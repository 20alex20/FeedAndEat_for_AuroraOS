#include "HomeFeature.h"
#include <QtQml>

HomeFeature::HomeFeature(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr)
{ }

HomeFeature::HomeFeature(DatabaseHandler * const databaseHandler, QObject *parent):
    QObject(parent),
    _databaseHandler(databaseHandler)
{
    qmlRegisterType<HomeViewModel>("FeadAndEat.Feature.Home", 1, 0, "HomeViewModel");
    qmlRegisterType<HomeViewModelState>("FeadAndEat.Feature.Home", 1, 0, "HomeViewModelState");
    qRegisterMetaType<Recipe*>("Recipe*");
    qRegisterMetaType<HomeViewModelState::Status>("HomeViewModelState::Status");
}

HomeViewModel *HomeFeature::getHomeViewModel(QObject *parent) {
    return new HomeViewModel(_databaseHandler, parent);
}
