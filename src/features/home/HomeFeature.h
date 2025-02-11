#ifndef HOMEFEATURE_H
#define HOMEFEATURE_H

#include "pres/HomeViewModel.h"

class HomeFeature : public QObject
{
    Q_OBJECT
public:
    explicit HomeFeature(QObject *parent = nullptr);
    explicit HomeFeature(DatabaseHandler * const databaseHandler, QObject *parent = nullptr);

    Q_INVOKABLE HomeViewModel *getHomeViewModel(QObject *parent = nullptr);

private:
    DatabaseHandler *_databaseHandler;
};

#endif // HOMEFEATURE_H
