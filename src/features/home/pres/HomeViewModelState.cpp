#include "HomeViewModelState.h"
#include <QDebug>

namespace {

void setRecipesParent(QList<Recipe*> recipes[], QObject *parent) {
    for (int i = 0; i < 4; i++)
        for (auto &recipe: recipes[i])
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
    if (_dailyRecipe != nullptr)
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
    qDebug() << "a8";
    if (_dailyRecipe != nullptr)
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
    qDebug() << "a8.1";
}

Recipe *HomeViewModelState::getDailyRecipe() {
    return _dailyRecipe;
}

QVariantList HomeViewModelState::getVariantList(HomeViewModelState::Collection collection) {
    QVariantList recipes;
    for (auto &recipe: _collectionsRecipes[collection - Qt::UserRole - 1])
        recipes.append(QVariant::fromValue<Recipe*>(recipe));
    return recipes;
}

QVariantList HomeViewModelState::getBreakfastRecipes() {
    return getVariantList(Breakfast);
}

HomeViewModelState::Status HomeViewModelState::getBreakfastRecipesStatus() {
    return _collectionsRecipesStatuses[Breakfast - Qt::UserRole - 1];
}

QVariantList HomeViewModelState::getDrinkRecipes() {
    return getVariantList(Drink);
}

HomeViewModelState::Status HomeViewModelState::getDrinkRecipesStatus() {
    return _collectionsRecipesStatuses[Drink - Qt::UserRole - 1];
}

QVariantList HomeViewModelState::getRecipesForBigGroup() {
    return getVariantList(ForBigGroup);
}

HomeViewModelState::Status HomeViewModelState::getRecipesForBigGroupStatus() {
    return _collectionsRecipesStatuses[ForBigGroup - Qt::UserRole - 1];
}

QVariantList HomeViewModelState::getLowCalorieRecipes() {
    return getVariantList(LowCalorie);
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
