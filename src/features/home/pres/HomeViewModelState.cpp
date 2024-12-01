#include "HomeViewModelState.h"

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
        _collectionsRecipes[i] = oldState->getCollectionRecipesList(i);
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
        _collectionsRecipes[i] = oldState->getCollectionRecipesList(i);
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
            _collectionsRecipes[i] = oldState->getCollectionRecipesList(i);
            _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
        }
    setRecipesParent(_collectionsRecipes, this);
}

HomeViewModelState::HomeViewModelState(HomeViewModelState *oldState, Collection collection, QList<Recipe*> &recipes, QObject *parent)
    : QObject(parent),
      _dailyRecipe(oldState->getDailyRecipe())
{
    if (_dailyRecipe != nullptr)
        _dailyRecipe->setParent(this);
    for (int i = 0; i < 4; i++)
        if (i + Qt::UserRole + 1 == collection) {
            _collectionsRecipes[i] = recipes;
            _collectionsRecipesStatuses[i] = recipes.isEmpty() ? Error : Success;
        }
        else {
            _collectionsRecipes[i] = oldState->getCollectionRecipesList(i);
            _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
        }
    setRecipesParent(_collectionsRecipes, this);
}

Recipe *HomeViewModelState::getDailyRecipe() {
    return _dailyRecipe;
}

QVariantList HomeViewModelState::getCollectionRecipes(HomeViewModelState::Collection collection) {
    QVariantList recipes;
    for (auto &recipe: _collectionsRecipes[collection - Qt::UserRole - 1])
        recipes.append(QVariant::fromValue<Recipe*>(recipe));
    return recipes;
}

HomeViewModelState::Status HomeViewModelState::getCollectionStatus(HomeViewModelState::Collection collection) {
    return _collectionsRecipesStatuses[collection - Qt::UserRole - 1];
}

Recipe *HomeViewModelState::getRecipe(HomeViewModelState::Collection collection, int index) {
    if (index < 0 || index >= _collectionsRecipes[collection - Qt::UserRole - 1].size())
        return new Recipe(this);
    return _collectionsRecipes[collection - Qt::UserRole - 1][index];
}

QList<Recipe*> HomeViewModelState::getCollectionRecipesList(int index) {
    if (index < 0 || index >= 4)
        return { };
    return _collectionsRecipes[index];
}

HomeViewModelState::Status HomeViewModelState::getCollectionRecipesStatus(int index) {
    if (index < 0 || index >= 4)
        return { };
    return _collectionsRecipesStatuses[index];
}
