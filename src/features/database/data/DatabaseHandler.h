#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "../domain/RecipesReplay.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    RecipesReplay *getRecipe(const int recipeId);
    RecipesReplay *getDailyRecipe();
    RecipesReplay *getHomepageCollection(QString collectionName);
    RecipesReplay *getSearchRecipes(QString searchString, QString category, const int continuation = -1);

private:
    QNetworkAccessManager * const _networkManager;
};

#endif // DATABASEHANDLER_H
