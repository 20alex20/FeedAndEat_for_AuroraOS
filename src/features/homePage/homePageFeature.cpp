#include "homePageFeature.h"
#include <QtQml>

HomePageFeature::HomePageFeature(DatabaseHandler *databaseHandler, QObject *parent):
    QObject(parent),
    _databaseHandler(databaseHandler)
{
    qmlRegisterType<HomePageViewModel>("FeadAndEat.Feature.HomePage", 1, 0, "HomePageViewModel");
}

HomePageViewModel *HomePageFeature::getHomePageViewModel(QObject *parent) {
    return new HomePageViewModel(_databaseHandler, parent);
}
