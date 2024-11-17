#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <memory>
#include "../domain/RecipesReplay.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);

    std::shared_ptr<RecipesReplay> getRecipe(const int recipeId);
    std::shared_ptr<RecipesReplay> getDailyRecipe();
    std::shared_ptr<RecipesReplay> getHomepageCollection(QString collectionName);
    std::shared_ptr<RecipesReplay> getSearchRecipes(QString searchString, QString category, const int continuation = -1);

private:
    QNetworkAccessManager *_networkManager;
};

#endif // DATABASEHANDLER_H
