#include "SearchViewModel.h"
#include "src/Default.h"

SearchViewModel::SearchViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr),
      _state(new SearchViewModelState()),
      _newRecipesReplays(),
      _additionalRecipesReplay({ nullptr, { "", "" } }),
      _recipesReplays()
{ }

SearchViewModel::SearchViewModel(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler),
      _state(new SearchViewModelState()),
      _newRecipesReplays(),
      _additionalRecipesReplay({ nullptr, { "", "" } }),
      _recipesReplays()
{ }

SearchViewModel::~SearchViewModel() {
    _state->deleteLater();
}

void SearchViewModel::bind() {
    _newRecipesReplays = { { _databaseHandler->getSearchRecipes("", ""), { "", "" } } };
    connect(_newRecipesReplays.first().first, &RecipesReplay::receive, this, &SearchViewModel::receiveNewRecipes);
}

void SearchViewModel::loadBySearchQuery(QString searchQuery) {
    QString category = _state->getCategory();
    setState(new SearchViewModelState(searchQuery, category));
    _newRecipesReplays.append({ _databaseHandler->getSearchRecipes(searchQuery, category), { searchQuery, category } });
    connect(_newRecipesReplays.last().first, &RecipesReplay::receive, this, &SearchViewModel::receiveNewRecipes);
}

void SearchViewModel::loadFromCategory(QString category) {
    QString searchQuery = _state->getSearchQuery();
    setState(new SearchViewModelState(searchQuery, category));
    _newRecipesReplays.append({ _databaseHandler->getSearchRecipes(searchQuery, category), { searchQuery, category } });
    connect(_newRecipesReplays.last().first, &RecipesReplay::receive, this, &SearchViewModel::receiveNewRecipes);
}

void SearchViewModel::receiveNewRecipes(QList<Recipe*> recipes) {
    QString searchQuery = _state->getSearchQuery();
    QString category = _state->getCategory();
    if (recipes.size() == Default::PageLength + 1) {
        setState(new SearchViewModelState(_state, recipes.mid(0, Default::PageLength), recipes[Default::PageLength]->getId()));
        recipes[Default::PageLength]->deleteLater();
    }
    else {
        setState(new SearchViewModelState(_state, recipes));
    }
    _newRecipesReplay.first->deleteLater();
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

