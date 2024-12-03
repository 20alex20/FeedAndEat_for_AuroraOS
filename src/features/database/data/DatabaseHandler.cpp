#include "DatabaseHandler.h"
#include <QDate>
#include "../domain/RecipeReply.h"
#include "../domain/DailyRecipeReply.h"
#include "../domain/HomepageCollectionReply.h"
#include "../domain/SearchRecipesReply.h"

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent),
      _networkManager(new QNetworkAccessManager(this))
{ }

RecipesReply *DatabaseHandler::getRecipe(const int recipeId) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    return new RecipeReply(QUrl(url), _networkManager, recipeId);
}

RecipesReply *DatabaseHandler::getDailyRecipe() {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/dayOfYearAndRecipeId.json?orderBy=\"dayOfYear\"&equalTo=" + QString::number(QDate::currentDate().dayOfYear() - 1);
    return new DailyRecipeReply(QUrl(url), _networkManager);
}

RecipesReply *DatabaseHandler::getHomepageCollection(QString collectionName) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/homepageCollections/" + collectionName + ".json";
    return new HomepageCollectionReply(QUrl(url), _networkManager);
}

RecipesReply *DatabaseHandler::getSearchRecipes(QString searchQuery, QString category, const int continuation) {
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipeIdAndName";
    if (category != "")
        url += "ByCategories/" + category.toLower();
    if (searchQuery != "")
        url += ".json?orderBy=\"name\"&startAt=\"" + searchQuery.toLower() + "\"&endAt=\"" + searchQuery.toLower() + "~\"";
    else if (continuation == -1)
        url += ".json?orderBy=\"recipeId\"&limitToFirst=" + QString::number(Default::PageLength + 1);
    else
        url += ".json?orderBy=\"recipeId\"&startAt=" + QString::number(continuation) + "&limitToFirst=" + QString::number(Default::PageLength + 1);
    return new SearchRecipesReply(QUrl(url), _networkManager);
}
