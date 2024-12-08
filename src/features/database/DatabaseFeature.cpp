#include "DatabaseFeature.h"
#include <QtQml>

DatabaseFeature::DatabaseFeature()
    : _databaseHandler(new DatabaseHandler())
{
    qmlRegisterType<Recipe>("FeadAndEat.Recipe", 1, 0, "Recipe");
}

DatabaseFeature::~DatabaseFeature()
{
    _databaseHandler->deleteLater();
}

DatabaseHandler *DatabaseFeature::getDatabaseHandler() {
    return _databaseHandler;
}
