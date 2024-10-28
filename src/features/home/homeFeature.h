#ifndef HOMEPAGEFEATURE_H
#define HOMEPAGEFEATURE_H

#include "pres/homePageViewModel.h"

class HomePageFeature : public QObject
{
    Q_OBJECT
public:
    explicit HomePageFeature(DatabaseHandler *databaseHandler, QObject *parent = nullptr);

    Q_INVOKABLE HomePageViewModel *getHomePageViewModel(QObject *parent = nullptr);

private:
    DatabaseHandler *_databaseHandler;
};

#endif // HOMEPAGEFEATURE_H
