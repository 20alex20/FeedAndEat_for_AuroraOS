#ifndef SEARCHVIEWMODELSTATE_H
#define SEARCHVIEWMODELSTATE_H

#include <QObject>
#include "src/features/database/domain/Recipe.h"

class SearchViewModelState : public QObject
{
    Q_OBJECT
public:
    explicit SearchViewModelState(QObject *parent = nullptr);
    explicit SearchViewModelState(QString searchQuery, QString category, QObject *parent = nullptr);
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
    int getRecipesNumber();
    int getContinuation();
    Status getStatus();

private:
    QString _searchQuery;
    QString _category;
    QList<Recipe*> _recipes;
    int _continuation;
    Status _status;
};

#endif // SEARCHVIEWMODELSTATE_H
