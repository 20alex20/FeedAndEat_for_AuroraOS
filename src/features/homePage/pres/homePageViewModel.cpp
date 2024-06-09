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
}

void HomePageViewModel::receiveRecipeIdOfDayOfYear(const int recipeId) {
    auto recipeReplay = _databaseHandler->getRecipe(recipeId);
    connect(recipeReplay, &RecipeReplay::receive, this, &HomePageViewModel::receiveRecipeOfDayOfYear);
}

void HomePageViewModel::receiveRecipeOfDayOfYear(const int recipeId, QJsonObject recipe) {
    _recipeOfDayOfYear = QString::number(recipeId) + ": " + recipe.toVariantMap()["amountOfServings"].toString();
    emit recipeOfDayOfYearChanged();
}

QString HomePageViewModel::getRecipeOfDayOfYear() {
    return _recipeOfDayOfYear;
}

void HomePageViewModel::receiveRecipesOfHomepageCollection(QString &collectionName, QList<QJsonObject> recipes) {
    if (collectionName == QString("breakfast")) {
        _recipesOfBreakfast = collectionName + ": " + QString::number(recipes.size());
        emit recipesOfBreakfastChanged();
    }
    else if (collectionName == QString("drink")) {
        _recipesOfDrink = collectionName + ": " + recipes[0].toVariantMap()["id"].toString();
        emit recipesOfDrinkChanged();
    }
    else if (collectionName == QString("forBigGroup")) {
        _recipesOfForBigGroup = collectionName + ": " + QString::number(recipes.size());
        emit recipesOfForBigGroupChanged();
    }
    else {
        _recipesOfLowCalorie = collectionName + ": " + QString::number(recipes.size());
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
