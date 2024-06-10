#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "../models/recipeReplay.h"
#include "../models/recipeIdOfDayOfYearReplay.h"
#include "../models/recipesOfHomepageCollectionReplay.h"
#include "../models/recipeIdsReplay.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    RecipeReplay* getRecipe(const int recipeId);
    RecipeIdOfDayOfYearReplay* getRecipeIdOfDayOfYear();
    RecipesOfHomepageCollectionReplay* getRecipesOfHomepageCollection(QString collectionName);
    RecipeIdsReplay* getRecipeIds(QString searchString, QString category = "");

private:
    QNetworkAccessManager *_networkManager;
};

#endif // DATABASEHANDLER_H
