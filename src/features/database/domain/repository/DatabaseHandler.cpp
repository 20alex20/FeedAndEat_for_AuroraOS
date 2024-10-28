#include "DatabaseHandler.h"
#include <QDate>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent),
      _networkManager(new QNetworkAccessManager(this))
{ }

std::shared_ptr<RecipesReplay> DatabaseHandler::getRecipe(const int recipeId) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    return std::make_shared<RecipeReplay>(QUrl(url), _networkManager);
}

std::shared_ptr<RecipesReplay> DatabaseHandler::getDailyRecipe() {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/dayOfYearAndRecipeId.json?orderBy=\"dayOfYear\"&equalTo=" + QString::number(QDate::currentDate().dayOfYear() - 1);
    return std::make_shared<DailyRecipeReplay>(QUrl(url), _networkManager);
}

std::shared_ptr<RecipesReplay> DatabaseHandler::getHomepageCollection(QString collectionName) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/homepageCollections/" + collectionName + ".json";
    return std::make_shared<HomepageCollectionReplay>(QUrl(url), _networkManager);
}

std::shared_ptr<RecipesReplay> DatabaseHandler::getSearchRecipes(QString searchString, QString category, const int continuation) {
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipeIdAndName";
    if (category != "")
        url += "ByCategories/" + category;
    if (searchString != "")
        url += ".json?orderBy=\"name\"&startAt=\"" + searchString.toLower() + "\"&endAt=\"" + searchString.toLower() + "~\"";
    else if (continuation == -1)
        url += ".json?orderBy=\"id\"&limitToFirst=" + QString::number(Default::PageLength + 1);
    else
        url += ".json?orderBy=\"id\"&startAt=" + QString::number(continuation) + "&limitToFirst=" + QString::number(Default::PageLength + 1);
    return std::make_shared<SearchRecipesReplay>(QUrl(url), _networkManager);
}
