#include "databaseHandler.h"
#include <QDate>

DatabaseHandler::DatabaseHandler(QObject *parent):
    QObject(parent),
    _networkManager(new QNetworkAccessManager(this))
{

}

RecipeReplay* DatabaseHandler::getRecipe(const int recipeId) {
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    auto recipeReplay = _networkManager->get(QNetworkRequest(QUrl(url)));
    return new RecipeReplay(recipeId, recipeReplay, _networkManager);
}

RecipeIdOfDayOfYearReplay* DatabaseHandler::getRecipeIdOfDayOfYear() {
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/dayOfYearAndRecipeId.json?orderBy=\"dayOfYear\"&equalTo=" + QString::number(QDate::currentDate().dayOfYear() - 1);
    auto recipeIdReplay = _networkManager->get(QNetworkRequest(QUrl(url)));
    return new RecipeIdOfDayOfYearReplay(recipeIdReplay, _networkManager);
}

RecipesOfHomepageCollectionReplay* DatabaseHandler::getRecipesOfHomepageCollection(QString collectionName){
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/homepageCollections/" + collectionName + ".json";
    auto recipesReplay = _networkManager->get(QNetworkRequest(QUrl(url)));
    return new RecipesOfHomepageCollectionReplay(collectionName, recipesReplay, _networkManager);
}

RecipeIdsReplay* DatabaseHandler::getRecipeIds(QString searchString, QString category) {
    QString url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipeIdAndName";
    if (category != "")
        url += "ByCategories/" + category;
    QString lowerSearchString = searchString.toLower();
    url += ".json?orderBy=\"name\"&startAt=\"" + lowerSearchString + "\"&endAt=\"" + lowerSearchString + "~\"";
    auto recipeIdsReplay = _networkManager->get(QNetworkRequest(QUrl(url)));
    return new RecipeIdsReplay(recipeIdsReplay, _networkManager);
}
