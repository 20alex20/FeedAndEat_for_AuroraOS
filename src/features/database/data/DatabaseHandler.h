#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "../domain/RecipesReply.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    RecipesReply *getRecipe(int recipeId);
    RecipesReply *getDailyRecipe();
    RecipesReply *getHomepageCollection(const QString &collectionName);
    RecipesReply *getSearchRecipes(const QString &searchQuery, const QString &category, int continuation = -1);

private:
    QNetworkAccessManager * const _networkManager;
};

#endif // DATABASEHANDLER_H
