#include "SearchViewModelState.h"

namespace {

void setRecipesParent(QList<Recipe*> &recipes, QObject *parent) {
    for (auto &recipe: recipes)
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

SearchViewModelState::SearchViewModelState(QString searchQuery, QString category, QList<Recipe*> recipes, int continuation, QObject *parent)
    : QObject(parent),
      _searchQuery(searchQuery),
      _category(category),
      _recipes(recipes),
      _continuation(continuation),
      _status(Loading)
{
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(const SearchViewModelState *oldState, const QList<Recipe*> &recipes, int continuation, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipesList() + recipes),
      _continuation(continuation),
      _status(Success)
{
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(const SearchViewModelState *oldState, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipesList()),
      _continuation(oldState->getContinuation()),
      _status(Error)
{
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(const SearchViewModelState *oldState, int index, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipesList()),
      _continuation(oldState->getContinuation()),
      _status(oldState->getStatus())
{
    if (index >= 0 && index < _recipes.size())
        _recipes[index] = nullptr;
    setRecipesParent(_recipes, this);
}

SearchViewModelState::SearchViewModelState(const SearchViewModelState *oldState, int index, Recipe *recipe, QObject *parent)
    : QObject(parent),
      _searchQuery(oldState->getSearchQuery()),
      _category(oldState->getCategory()),
      _recipes(oldState->getRecipesList()),
      _continuation(oldState->getContinuation()),
      _status(oldState->getStatus())
{
    if (index >= 0 && index < _recipes.size())
        _recipes[index] = recipe;
    setRecipesParent(_recipes, this);
}

Recipe *SearchViewModelState::getRecipe(int index) {
    if (index < 0 || index >= _recipes.size())
        return new Recipe(this);
    return _recipes[index];
}

QString SearchViewModelState::getSearchQuery() const {
    return _searchQuery;
}

QVariantList SearchViewModelState::getRecipes() const {
    QVariantList recipes;
    recipes.reserve(_recipes.size());
    for (auto &recipe: _recipes)
        recipes.append(QVariant::fromValue<Recipe*>(recipe));
    return recipes;
}

int SearchViewModelState::getRecipesNumber() const {
    return _recipes.size();
}

bool SearchViewModelState::isEnd() const {
    return _continuation == -1;
}

SearchViewModelState::Status SearchViewModelState::getStatus() const {
    return _status;
}

QString SearchViewModelState::getCategory() const {
    return _category;
}

QList<Recipe*> SearchViewModelState::getRecipesList() const {
    return _recipes;
}

int SearchViewModelState::getContinuation() const {
    return _continuation;
}
