#ifndef SEARCHVIEWMODELSTATE_H
#define SEARCHVIEWMODELSTATE_H

#include <QObject>
#include "src/features/database/domain/Recipe.h"

class SearchViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchQuery READ getSearchQuery CONSTANT)
    Q_PROPERTY(QString category READ getCategory CONSTANT)
    Q_PROPERTY(QList<Recipe*> recipes READ getRecipes CONSTANT)
    Q_PROPERTY(bool isEnd READ isEnd CONSTANT)
    Q_PROPERTY(Status status READ getStatus CONSTANT)
public:
    explicit SearchViewModelState(QObject *parent = nullptr);
    explicit SearchViewModelState(QString searchQuery, QString category = "", QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, QList<Recipe*> recipes, int continuation = -1, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, int index, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, int index, Recipe *recipe, QObject *parent = nullptr);

    enum Status {
        Loading = Qt::UserRole + 1,
        Success,
        Error
    };
    Q_ENUM(Status)

    QString getSearchQuery();
    QString getCategory();
    QList<Recipe*> getRecipes();
    Recipe* getRecipe(int index);
    int getRecipesNumber();
    int getContinuation();
    bool isEnd();
    Status getStatus();

private:
    QString _searchQuery;
    QString _category;
    QList<Recipe*> _recipes;
    int _continuation;
    Status _status;
};

#endif // SEARCHVIEWMODELSTATE_H
