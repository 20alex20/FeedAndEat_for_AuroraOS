#include "HomeViewModelState.h"

namespace {

void setRecipesParent(QList<Recipe*> recipes[], QObject *parent) {
    for (int i = 0; i < 4; i++)
        for (auto recipe: recipes[i])
            recipe->setParent(parent);
}

}

HomeViewModelState::HomeViewModelState(QObject *parent)
    : QObject(parent),
      _dailyRecipe(nullptr),
      _collectionsRecipes()
{
    for (int i = 0; i < 4; i++)
        _collectionsRecipesStatuses[i] = Loading;
}

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, QObject *parent)
    : QObject(parent),
      _dailyRecipe(nullptr)
{
    for (int i = 0; i < 4; i++) {
        _collectionsRecipes[i] = oldState->getCollectionRecipes(i);
        _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
    }
    setRecipesParent(_collectionsRecipes, this);
}

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, Recipe *dailyRecipe, QObject *parent)
    : QObject(parent),
      _dailyRecipe(dailyRecipe)
{
    _dailyRecipe->setParent(this);
    for (int i = 0; i < 4; i++) {
        _collectionsRecipes[i] = oldState->getCollectionRecipes(i);
        _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
    }
    setRecipesParent(_collectionsRecipes, this);
}

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, Collection collection, QObject *parent)
    : QObject(parent),
      _dailyRecipe(oldState->getDailyRecipe())
{
    _dailyRecipe->setParent(this);
    for (int i = 0; i < 4; i++)
        if (i + Qt::UserRole + 1 == collection) {
            _collectionsRecipesStatuses[i] = Loading;
        }
        else {
            _collectionsRecipes[i] = oldState->getCollectionRecipes(i);
            _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
        }
    setRecipesParent(_collectionsRecipes, this);
}

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, Collection collection, QList<Recipe*> &recipes, QObject *parent)
    : QObject(parent),
      _dailyRecipe(oldState->getDailyRecipe())
{
    _dailyRecipe->setParent(this);
    for (int i = 0; i < 4; i++)
        if (i + Qt::UserRole + 1 == collection) {
            _collectionsRecipes[i] = recipes;
            _collectionsRecipesStatuses[i] = recipes.isEmpty() ? Error : Success;
        }
        else {
            _collectionsRecipes[i] = oldState->getCollectionRecipes(i);
            _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
        }
    setRecipesParent(_collectionsRecipes, this);
}

Recipe *HomeViewModelState::getDailyRecipe() {
    return _dailyRecipe;
}

QList<Recipe*> HomeViewModelState::getBreakfastRecipes() {
    return _collectionsRecipes[Breakfast - Qt::UserRole - 1];
}

HomeViewModelState::Status HomeViewModelState::getBreakfastRecipesStatus() {
    return _collectionsRecipesStatuses[Breakfast - Qt::UserRole - 1];
}

QList<Recipe*> HomeViewModelState::getDrinkRecipes() {
    return _collectionsRecipes[Drink - Qt::UserRole - 1];
}

HomeViewModelState::Status HomeViewModelState::getDrinkRecipesStatus() {
    return _collectionsRecipesStatuses[Drink - Qt::UserRole - 1];
}

QList<Recipe*> HomeViewModelState::getRecipesForBigGroup() {
    return _collectionsRecipes[ForBigGroup - Qt::UserRole - 1];
}

HomeViewModelState::Status HomeViewModelState::getRecipesForBigGroupStatus() {
    return _collectionsRecipesStatuses[ForBigGroup - Qt::UserRole - 1];
}

QList<Recipe*> HomeViewModelState::getLowCalorieRecipes() {
    return _collectionsRecipes[LowCalorie - Qt::UserRole - 1];
}

HomeViewModelState::Status HomeViewModelState::getLowCalorieRecipesStatus() {
    return _collectionsRecipesStatuses[LowCalorie - Qt::UserRole - 1];
}

QList<Recipe*> HomeViewModelState::getCollectionRecipes(int index) {
    return _collectionsRecipes[index];
}

HomeViewModelState::Status HomeViewModelState::getCollectionRecipesStatus(int index) {
    return _collectionsRecipesStatuses[index];
}
