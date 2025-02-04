#include "DatabaseFeature.h"
#include <QtQml>

DatabaseFeature::DatabaseFeature()
    : _databaseHandler(new DatabaseHandler())
{
    qmlRegisterType<Recipe>("FeedAndEat.Recipe", 1, 0, "Recipe");
}

DatabaseFeature::~DatabaseFeature()
{
    _databaseHandler->deleteLater();
}

DatabaseHandler *DatabaseFeature::getDatabaseHandler() {
    return _databaseHandler;
}
