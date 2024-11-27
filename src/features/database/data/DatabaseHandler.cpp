#include "DatabaseHandler.h"
#include <QDate>
#include "../domain/RecipeReplay.h"
#include "../domain/DailyRecipeReplay.h"
#include "../domain/HomepageCollectionReplay.h"
#include "../domain/SearchRecipesReplay.h"
#include <QDebug>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent),
      _networkManager(new QNetworkAccessManager(this))
{ }

RecipesReplay *DatabaseHandler::getRecipe(const int recipeId) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    return new RecipeReplay(QUrl(url), _networkManager, recipeId);
}

RecipesReplay *DatabaseHandler::getDailyRecipe() {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/dayOfYearAndRecipeId.json?orderBy=\"dayOfYear\"&equalTo=" + QString::number(QDate::currentDate().dayOfYear() - 1);
    return new DailyRecipeReplay(QUrl(url), _networkManager);
}

RecipesReplay *DatabaseHandler::getHomepageCollection(QString collectionName) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/homepageCollections/" + collectionName + ".json";
    return new HomepageCollectionReplay(QUrl(url), _networkManager);
}

RecipesReplay *DatabaseHandler::getSearchRecipes(QString searchQuery, QString category, const int continuation) {
    qDebug() << "b2";
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipeIdAndName";
    if (category != "")
        url += "ByCategories/" + category.toLower();
    if (searchQuery != "")
        url += ".json?orderBy=\"name\"&startAt=\"" + searchQuery.toLower() + "\"&endAt=\"" + searchQuery.toLower() + "~\"";
    else if (continuation == -1)
        url += ".json?orderBy=\"recipeId\"&limitToFirst=" + QString::number(Default::PageLength + 1);
    else
        url += ".json?orderBy=\"recipeId\"&startAt=" + QString::number(continuation) + "&limitToFirst=" + QString::number(Default::PageLength + 1);
    return new SearchRecipesReplay(QUrl(url), _networkManager);
}
