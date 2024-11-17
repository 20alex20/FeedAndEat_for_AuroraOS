#include "HomeViewModelState.h"

HomeViewModelState::HomeViewModelState(QObject *parent)
    : QObject(parent),
      _dailyRecipe(),
      _breakfastRecipes(),
      _drinkRecipes(),
      _recipesForBigGroup(),
      _lowCalorieRecipes()
{ }

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, Recipe &dailyRecipe, QObject *parent)
    : QObject(parent),
      _dailyRecipe(dailyRecipe),
      _breakfastRecipes(oldState->getBreakfastRecipes()),
      _drinkRecipes(oldState->getDrinkRecipes()),
      _recipesForBigGroup(oldState->getRecipesForBigGroup()),
      _lowCalorieRecipes(oldState->getLowCalorieRecipes())
{ }

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, QString collectionName, QList<Recipe> &recipes, QObject *parent)
    : QObject(parent),
      _dailyRecipe(oldState->getDailyRecipe()),
      _breakfastRecipes(collectionName == "breakfast" ? recipes : oldState->getBreakfastRecipes()),
      _drinkRecipes(collectionName == "drink" ? recipes : oldState->getDrinkRecipes()),
      _recipesForBigGroup(collectionName == "forBigGroup" ? recipes : oldState->getRecipesForBigGroup()),
      _lowCalorieRecipes(collectionName == "lowCalorie" ? recipes : oldState->getLowCalorieRecipes())
{ }

Recipe HomeViewModelState::getDailyRecipe() {
    return _dailyRecipe;
}

QList<Recipe> HomeViewModelState::getBreakfastRecipes() {
    return _breakfastRecipes;
}

QList<Recipe> HomeViewModelState::getDrinkRecipes() {
    return _drinkRecipes;
}

QList<Recipe> HomeViewModelState::getRecipesForBigGroup() {
    return _recipesForBigGroup;
}

QList<Recipe> HomeViewModelState::getLowCalorieRecipes() {
    return _lowCalorieRecipes;
}
