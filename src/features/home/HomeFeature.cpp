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
    qmlRegisterType<HomeViewModel>("FeedAndEat.Feature.Home", 1, 0, "HomeViewModel");
    qmlRegisterType<HomeViewModelState>("FeedAndEat.Feature.Home", 1, 0, "HomeViewModelState");
    qRegisterMetaType<HomeViewModelState::Status>("HomeViewModelState::Status");
    qRegisterMetaType<HomeViewModelState::Collection>("HomeViewModelState::Collection");
}

HomeViewModel *HomeFeature::getHomeViewModel(QObject *parent) {
    return new HomeViewModel(_databaseHandler, parent);
}
