#include "homePageViewModel.h"

HomePageViewModel::HomePageViewModel(QObject *parent):
    QObject(parent),
    _databaseHandler(nullptr)
{

}

HomePageViewModel::HomePageViewModel(DatabaseHandler *databaseHandler, QObject *parent):
    QObject(parent),
    _databaseHandler(databaseHandler)
{

}

void HomePageViewModel::bind() {
    connect(_databaseHandler->getRecipeIdOfDayOfYear(), &RecipeIdOfDayOfYearReplay::receive,
            this, &HomePageViewModel::receiveRecipeIdOfDayOfYear);
    connect(_databaseHandler->getRecipesOfHomepageCollection("breakfast"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomePageViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("drink"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomePageViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("forBigGroup"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomePageViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("lowCalorie"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomePageViewModel::receiveRecipesOfHomepageCollection);

    connect(_databaseHandler->getRecipeIds("East"), &RecipeIdsReplay::receive,
            this, &HomePageViewModel::receiveRecipeIds);
    connect(_databaseHandler->getRecipe(738), &RecipeReplay::receive,
            this, &HomePageViewModel::receiveRecipe);
}

void HomePageViewModel::receiveRecipeIdOfDayOfYear(const int recipeId) {
    connect(_databaseHandler->getRecipe(recipeId), &RecipeReplay::receive, this, &HomePageViewModel::receiveRecipeOfDayOfYear);
}

void HomePageViewModel::receiveRecipeOfDayOfYear(const int recipeId, QJsonObject recipe) {
    _recipeOfDayOfYear = recipe.toVariantMap()["id"].toString();
    emit recipeOfDayOfYearChanged();
}

QString HomePageViewModel::getRecipeOfDayOfYear() {
    return _recipeOfDayOfYear;
}

void HomePageViewModel::receiveRecipesOfHomepageCollection(QString &collectionName, QList<QJsonObject> recipes) {
    if (collectionName == QString("breakfast")) {
        _recipesOfBreakfast = collectionName + ": " + recipes[0].toVariantMap()["id"].toString();
        emit recipesOfBreakfastChanged();
    }
    else if (collectionName == QString("drink")) {
        _recipesOfDrink = collectionName + ": " + recipes[0].toVariantMap()["id"].toString();
        emit recipesOfDrinkChanged();
    }
    else if (collectionName == QString("forBigGroup")) {
        _recipesOfForBigGroup = collectionName + ": " + recipes[0].toVariantMap()["id"].toString();
        emit recipesOfForBigGroupChanged();
    }
    else {
        _recipesOfLowCalorie = collectionName + ": " + recipes[0].toVariantMap()["id"].toString();
        emit recipesOfLowCalorieChanged();
    }
}

QString HomePageViewModel::getRecipesOfBreakfast() {
    return _recipesOfBreakfast;
}

QString HomePageViewModel::getRecipesOfDrink() {
    return _recipesOfDrink;
}

QString HomePageViewModel::getRecipesOfForBigGroup() {
    return _recipesOfForBigGroup;
}

QString HomePageViewModel::getRecipesOfLowCalorie() {
    return _recipesOfLowCalorie;
}

void HomePageViewModel::receiveRecipeIds(QList<int> recipeIds) {
    _recipeIds = "";
    for (int i = 0; i < recipeIds.size(); i++)
        _recipeIds += QString::number(recipeIds[i]) + ",";
    emit recipeIdsChanged();
}

QString HomePageViewModel::getRecipeIds() {
    return _recipeIds;
}

void HomePageViewModel::receiveRecipe(const int recipeId, QJsonObject recipe) {
    _recipe.append(QString::number(recipeId) + ": " + recipe.toVariantMap()["id"].toString());
    emit recipeChanged();
}

QString HomePageViewModel::getRecipe() {
    auto recipe = _recipe.first();
    _recipe.removeFirst();
    return recipe;
}
