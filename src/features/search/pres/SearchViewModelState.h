#ifndef SEARCHVIEWMODELSTATE_H
#define SEARCHVIEWMODELSTATE_H

#include <QObject>
#include <QVariantList>
#include "src/features/database/domain/Recipe.h"

class SearchViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchQuery READ getSearchQuery CONSTANT)
    Q_PROPERTY(QVariantList recipes READ getRecipes CONSTANT)
    Q_PROPERTY(int recipesNumber READ getRecipesNumber CONSTANT)
    Q_PROPERTY(bool isEnd READ isEnd CONSTANT)
    Q_PROPERTY(Status status READ getStatus CONSTANT)
public:
    enum Status {
        Loading = Qt::UserRole + 1,
        Success,
        Error
    };
    Q_ENUM(Status)

    explicit SearchViewModelState(QObject *parent = nullptr);
    explicit SearchViewModelState(QString searchQuery, QString category = "", QList<Recipe*> recipes = { }, int continuation = -1, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, QList<Recipe*> recipes, int continuation = -1, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, int index, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, int index, Recipe *recipe, QObject *parent = nullptr);

    QString getSearchQuery() const;
    QVariantList getRecipes() const;
    int getRecipesNumber() const;
    bool isEnd() const;
    Status getStatus() const;
    Q_INVOKABLE Recipe *getRecipe(int index);

    QString getCategory() const;
    QList<Recipe*> getRecipesList() const;
    int getContinuation() const;

private:
    QString _searchQuery;
    QString _category;
    QList<Recipe*> _recipes;
    int _continuation;
    Status _status;
};

#endif // SEARCHVIEWMODELSTATE_H
