#include "SearchViewModel.h"

SearchViewModel::SearchViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr),
      _state(new SearchViewModelState()),
      _newRecipesReplay({ nullptr, { "", "" } }),
      _additionalRecipesReplay({ nullptr, { "", "" } }),
      _recipesReplays()
{ }

SearchViewModel::SearchViewModel(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler),
      _state(new SearchViewModelState()),
      _newRecipesReplay({ nullptr, { "", "" } }),
      _additionalRecipesReplay({ nullptr, { "", "" } }),
      _recipesReplays()
{ }

SearchViewModel::~SearchViewModel() {
    _state->deleteLater();
}

void SearchViewModel::bind() {
    _newRecipesReplay = { _databaseHandler->getSearchRecipes("", ""), { "", "" } };
    connect(_newRecipesReplay.first, &RecipesReplay::receive, this, &SearchViewModel::receiveNewRecipes);
}

void SearchViewModel::receiveNewRecipes(QList<Recipe*> recipes) {
    setState(new SearchViewModelState(_state, recipes));
    _breakfastRecipesReplay->deleteLater();
}

void SearchViewModel::setState(SearchViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}

SearchViewModelState *SearchViewModel::getState() const {
    return _state;
}

