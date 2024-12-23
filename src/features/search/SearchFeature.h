#ifndef SEARCHFEATURE_H
#define SEARCHFEATURE_H

#include "pres/SearchViewModel.h"

class SearchFeature : public QObject
{
    Q_OBJECT
public:
    explicit SearchFeature(QObject *parent = nullptr);
    explicit SearchFeature(DatabaseHandler * const databaseHandler, QObject *parent = nullptr);

    Q_INVOKABLE SearchViewModel *getSearchViewModel(QObject *parent = nullptr);

private:
    DatabaseHandler *_databaseHandler;
};

#endif // SEARCHFEATURE_H
