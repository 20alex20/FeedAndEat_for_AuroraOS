#include "HomeFeature.h"
#include <QtQml>

HomeFeature::HomeFeature(DatabaseHandler * const databaseHandler, QObject *parent):
    QObject(parent),
    _databaseHandler(databaseHandler)
{
    qmlRegisterType<HomeViewModel>("FeadAndEat.Feature.Home", 1, 0, "HomePageViewModel");
}

HomeViewModel *HomeFeature::getHomePageViewModel(QObject *parent) {
    return new HomeViewModel(_databaseHandler, parent);
}
