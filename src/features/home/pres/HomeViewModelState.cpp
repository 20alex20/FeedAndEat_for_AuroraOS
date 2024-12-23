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

HomeViewModelState::HomeViewModelState(const HomeViewModelState *oldState, QObject *parent)
    : QObject(parent),
      _dailyRecipe(nullptr)
{
    for (int i = 0; i < 4; i++) {
        _collectionsRecipes[i] = oldState->getCollectionRecipesList(i);
        _collectionsRecipesStatuses[i] = oldState->getCollectionRecipesStatus(i);
    }
    setRecipesParent(_collectionsRecipes, this);
}

HomeViewModelState::HomeViewModelState(const HomeViewModelState *oldState, Recipe *dailyRecipe, QObject *parent)
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

HomeViewModelState::HomeViewModelState(const HomeViewModelState *oldState, Collection collection, QObject *parent)
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

HomeViewModelState::HomeViewModelState(const HomeViewModelState *oldState, Collection collection, const QList<Recipe*> &recipes, QObject *parent)
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

QVariantList HomeViewModelState::getCollectionRecipes(Collection collection) const {
    QVariantList recipes;
    recipes.reserve(_collectionsRecipes[collection - Qt::UserRole - 1].size());
    for (auto &recipe: _collectionsRecipes[collection - Qt::UserRole - 1])
        recipes.append(QVariant::fromValue<Recipe*>(recipe));
    return recipes;
}

HomeViewModelState::Status HomeViewModelState::getCollectionStatus(Collection collection) const {
    return _collectionsRecipesStatuses[collection - Qt::UserRole - 1];
}

Recipe *HomeViewModelState::getRecipe(Collection collection, int index) {
    if (index < 0 || index >= _collectionsRecipes[collection - Qt::UserRole - 1].size())
        return new Recipe(this);
    return _collectionsRecipes[collection - Qt::UserRole - 1][index];
}

Recipe *HomeViewModelState::getDailyRecipe() const {
    return _dailyRecipe;
}

QList<Recipe*> HomeViewModelState::getCollectionRecipesList(int index) const {
    if (index < 0 || index >= 4)
        return { };
    return _collectionsRecipes[index];
}

HomeViewModelState::Status HomeViewModelState::getCollectionRecipesStatus(int index) const {
    if (index < 0 || index >= 4)
        return { };
    return _collectionsRecipesStatuses[index];
}
