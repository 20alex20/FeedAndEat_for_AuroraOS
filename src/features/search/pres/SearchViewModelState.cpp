#include "SearchViewModelState.h"

namespace {

void setRecipesParent(QList<Recipe*> &recipes, QObject *parent) {
    for (auto recipe: recipes)
        if (recipe != nullptr)
            recipe->setParent(parent);
}

}

SearchViewModelState::SearchViewModelState(QObject *parent)
    : QObject(parent),
      _searchQuery(""),
      _category(""),
      _recipes(),
      _continuation(-1),
      _status(Loading)
{ }

SearchViewModelState::SearchViewModelState(QString searchQuery, QString category, QObject *parent)
    : QObject(parent),
      _searchQuery(searchQuery),
      _category(category),
      _recipes(),
      _continuation(-1),
      _status(Loading)
{ }

SearchViewModelState::SearchViewModelState(SearchViewModelState *oldState, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipes()),
      _continuation(oldState->getContinuation()),
      _status(Loading)
{
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(SearchViewModelState *oldState, QList<Recipe*> recipes, int continuation, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipes() + recipes),
      _continuation(recipes.isEmpty() ? oldState->getContinuation() : continuation),
      _status(recipes.isEmpty() ? Error : Success)
{
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(SearchViewModelState *oldState, int index, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipes()),
      _continuation(oldState->getContinuation()),
      _status(oldState->getStatus())
{
    if (index >= 0 && index < _recipes.size())
        _recipes[index] = nullptr;
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(SearchViewModelState *oldState, int index, Recipe *recipe, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipes()),
      _continuation(oldState->getContinuation()),
      _status(oldState->getStatus())
{
    if (index >= 0 && index < _recipes.size())
        _recipes[index] = recipe;
    setRecipesParent(_recipes, this);
}

QString SearchViewModelState::getSearchQuery() {
    return _searchQuery;
}

QString SearchViewModelState::getCategory() {
    return _category;
}

QList<Recipe*> SearchViewModelState::getRecipes() {
    return _recipes;
}

int SearchViewModelState::getRecipesNumber() {
    return _recipes.size();
}

int SearchViewModelState::getContinuation() {
    return _continuation;
}

SearchViewModelState::Status SearchViewModelState::getStatus() {
    return _status;
}
