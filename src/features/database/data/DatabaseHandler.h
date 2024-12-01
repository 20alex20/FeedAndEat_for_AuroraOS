#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "../domain/RecipesReply.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    RecipesReply *getRecipe(const int recipeId);
    RecipesReply *getDailyRecipe();
    RecipesReply *getHomepageCollection(QString collectionName);
    RecipesReply *getSearchRecipes(QString searchQuery, QString category, const int continuation = -1);

private:
    QNetworkAccessManager * const _networkManager;
};

#endif // DATABASEHANDLER_H
