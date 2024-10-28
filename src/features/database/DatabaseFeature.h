#ifndef DATABASEFEATURE_H
#define DATABASEFEATURE_H

#include "domain/repository/DatabaseHandler.h"

class DatabaseFeature
{
public:
    DatabaseFeature();
    ~DatabaseFeature();

    DatabaseHandler *getDatabaseHandler();

private:
    DatabaseHandler *_databaseHandler;
};

#endif // DATABASEFEATURE_H
