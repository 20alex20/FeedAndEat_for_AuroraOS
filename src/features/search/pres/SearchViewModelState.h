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
    explicit SearchViewModelState(QList<Recipe*> recipes, int continuation, QObject *parent = nullptr);
    explicit SearchViewModelState(SearchViewModelState *oldState, QList<Recipe*> recipes, int continuation, QObject *parent = nullptr);

    enum Status {
        Loading = Qt::UserRole + 1,
        Success,
        Error
    };

private:
    QString _searchQuery;
    QString _category;
    QList<Recipe> _recipes;
    Status _status;
    int _continuation;
};

#endif // SEARCHVIEWMODELSTATE_H
