#include "DatabaseFeature.h"

DatabaseFeature::DatabaseFeature()
    : _databaseHandler(new DatabaseHandler())
{ }

DatabaseFeature::~DatabaseFeature()
{
    _databaseHandler->deleteLater();
}

DatabaseHandler * DatabaseFeature::getDatabaseHandler() {
    return _databaseHandler;
}
