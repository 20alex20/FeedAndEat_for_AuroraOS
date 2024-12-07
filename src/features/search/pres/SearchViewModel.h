#ifndef SEARCHVIEWMODEL_H
#define SEARCHVIEWMODEL_H

#include <QPair>
#include "src/features/database/data/DatabaseHandler.h"
#include "SearchViewModelState.h"

class SearchViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SearchViewModelState *state READ getState NOTIFY stateChanged)
public:
    explicit SearchViewModel(QObject *parent = nullptr);
    explicit SearchViewModel(DatabaseHandler * const databaseHandler, QObject *parent = nullptr);
    ~SearchViewModel();

    Q_INVOKABLE void bind();
    Q_INVOKABLE void loadBySearchQuery(QString searchQuery);
    Q_INVOKABLE void loadFromCategory(QString category);
    Q_INVOKABLE void loadFromAllCategories();
    Q_INVOKABLE void loadAdditionalRecipes();
    Q_INVOKABLE void loadRecipe(int index);

    void receiveRecipes(RecipesReply *recipesReply, QList<Recipe*> recipes);
    void receiveRecipe(RecipesReply *recipeReply, QList<Recipe*> recipes);

    void setState(SearchViewModelState* newState);
    SearchViewModelState *getState() const;
signals:
    void stateChanged();

private:
    DatabaseHandler * const _databaseHandler;
    SearchViewModelState *_state;

    RecipesReply *_currentRecipesReply;
    QList<QPair<RecipesReply*, int>> _recipesReplies;
};

#endif // SEARCHVIEWMODEL_H
