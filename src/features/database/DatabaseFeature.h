#ifndef DATABASEFEATURE_H
#define DATABASEFEATURE_H

#include "data/DatabaseHandler.h"

class DatabaseFeature
{
public:
    DatabaseFeature();
    ~DatabaseFeature();

    DatabaseHandler *getDatabaseHandler();

private:
    DatabaseHandler * const _databaseHandler;
};

#endif // DATABASEFEATURE_H
