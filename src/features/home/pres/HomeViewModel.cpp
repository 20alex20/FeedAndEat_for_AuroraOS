#include "HomeViewModel.h"

HomeViewModel::HomeViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr)
{ }

HomeViewModel::HomeViewModel(DatabaseHandler *databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler)
{ }

void HomeViewModel::bind() {
    connect(_databaseHandler->getRecipeIdOfDayOfYear(), &RecipeIdOfDayOfYearReplay::receive,
            this, &HomeViewModel::receiveRecipeIdOfDayOfYear);
    connect(_databaseHandler->getRecipesOfHomepageCollection("breakfast"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomeViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("drink"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomeViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("forBigGroup"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomeViewModel::receiveRecipesOfHomepageCollection);
    connect(_databaseHandler->getRecipesOfHomepageCollection("lowCalorie"), &RecipesOfHomepageCollectionReplay::receive,
            this, &HomeViewModel::receiveRecipesOfHomepageCollection);

}

void HomeViewModel::receiveDailyRecipe(QList<QJsonObject> recipe) {
    _recipeOfDayOfYear = recipe.toVariantMap()["id"].toString();
    emit dailyRecipeChanged();
}

void HomeViewModel::receiveHomepageCollection(QList<QJsonObject> recipes) {
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

QString HomeViewModel::getRecipesOfBreakfast() {
    return _recipesOfBreakfast;
}

QString HomeViewModel::getRecipesOfDrink() {
    return _recipesOfDrink;
}

QString HomeViewModel::getRecipesOfForBigGroup() {
    return _recipesOfForBigGroup;
}

QString HomeViewModel::getRecipesOfLowCalorie() {
    return _recipesOfLowCalorie;
}

void HomeViewModel::receiveRecipeIds(QList<int> recipeIds) {
    _recipeIds = "";
    for (int i = 0; i < recipeIds.size(); i++)
        _recipeIds += QString::number(recipeIds[i]) + ",";
    emit recipeIdsChanged();
}

QString HomeViewModel::getRecipeIds() {
    return _recipeIds;
}

void HomeViewModel::receiveRecipe(const int recipeId, QJsonObject recipe) {
    _recipe.append(QString::number(recipeId) + ": " + recipe.toVariantMap()["id"].toString());
    emit recipeChanged();
}

QString HomeViewModel::getRecipe() {
    auto recipe = _recipe.first();
    _recipe.removeFirst();
    return recipe;
}
