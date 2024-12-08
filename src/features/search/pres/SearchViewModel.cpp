#include "SearchViewModel.h"
#include "src/Default.h"

SearchViewModel::SearchViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr),
      _state(new SearchViewModelState()),
      _currentRecipesReply(nullptr),
      _recipesReplies()
{ }

SearchViewModel::SearchViewModel(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler),
      _state(new SearchViewModelState()),
      _currentRecipesReply(nullptr),
      _recipesReplies()
{ }

SearchViewModel::~SearchViewModel() {
    _state->deleteLater();
}

void SearchViewModel::bind() {
    _recipesReplies.clear();
    _currentRecipesReply = _databaseHandler->getSearchRecipes(_state->getSearchQuery(), _state->getCategory());
    connect(_currentRecipesReply, &RecipesReply::receive, this, &SearchViewModel::receiveRecipes);
}

void SearchViewModel::loadBySearchQuery(QString searchQuery) {
    setState(new SearchViewModelState(searchQuery, _state->getCategory()));
    bind();
}

void SearchViewModel::loadFromCategory(QString category) {
    setState(new SearchViewModelState(_state->getSearchQuery(), category));
    bind();
}

void SearchViewModel::loadFromAllCategories() {
    setState(new SearchViewModelState(_state->getSearchQuery()));
    bind();
}

void SearchViewModel::loadAdditionalRecipes() {
    setState(new SearchViewModelState(_state->getSearchQuery(), _state->getCategory(), _state->getRecipesList(), _state->getContinuation()));
    _currentRecipesReply = _databaseHandler->getSearchRecipes(_state->getSearchQuery(), _state->getCategory(), _state->getContinuation());
    connect(_currentRecipesReply, &RecipesReply::receive, this, &SearchViewModel::receiveRecipes);
}

void SearchViewModel::loadRecipe(int index) {
    if (index < 0 || index >= _state->getRecipesNumber())
        return;
    auto recipeId = _state->getRecipe(index)->getId();
    if (recipeId == -1)
        return;
    setState(new SearchViewModelState(_state, index));
    _recipesReplies.append({ _databaseHandler->getRecipe(recipeId), index });
    connect(_recipesReplies.last().first, &RecipesReply::receive, this, &SearchViewModel::receiveRecipe);
}

SearchViewModelState *SearchViewModel::getState() const {
    return _state;
}

void SearchViewModel::setState(SearchViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}

void SearchViewModel::receiveRecipes(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    if (_currentRecipesReply == recipesReply) {
        if (recipesReply->getUrl().right(4) != "~%22" && recipes.size() == Default::PageLength + 1) {
            setState(new SearchViewModelState(_state, recipes.mid(0, Default::PageLength), recipes[Default::PageLength]->getId()));
            recipes[Default::PageLength]->deleteLater();
        }
        else if (recipes.size() == 1 && recipes[0] == nullptr) {
            setState(new SearchViewModelState(_state));
        }
        else {
            setState(new SearchViewModelState(_state, recipes));
        }
    }
    recipesReply->deleteLater();
}

void SearchViewModel::receiveRecipe(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    for (int i = 0; i < _recipesReplies.size(); i++)
        if (_recipesReplies[i].first == recipesReply) {
            setState(new SearchViewModelState(_state, _recipesReplies[i].second, recipes[0]));
            _recipesReplies.removeAt(i);
            break;
        }
    recipesReply->deleteLater();
}
