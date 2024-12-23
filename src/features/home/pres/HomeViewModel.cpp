#include "HomeViewModel.h"

HomeViewModel::HomeViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr),
      _state(new HomeViewModelState())
{ }

HomeViewModel::HomeViewModel(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler),
      _state(new HomeViewModelState())
{ }

HomeViewModel::~HomeViewModel() {
    _state->deleteLater();
}

void HomeViewModel::bind() {
    connect(_databaseHandler->getDailyRecipe(), &RecipesReply::receive, this, &HomeViewModel::receiveDailyRecipe);
    connect(_databaseHandler->getHomepageCollection("breakfast"), &RecipesReply::receive,
            this, &HomeViewModel::receiveBreakfastRecipes);
    connect(_databaseHandler->getHomepageCollection("drink"), &RecipesReply::receive,
            this, &HomeViewModel::receiveDrinkRecipes);
    connect(_databaseHandler->getHomepageCollection("forBigGroup"), &RecipesReply::receive,
            this, &HomeViewModel::receiveRecipesForBigGroup);
    connect(_databaseHandler->getHomepageCollection("lowCalorie"), &RecipesReply::receive,
            this, &HomeViewModel::receiveLowCalorieRecipes);
}

void HomeViewModel::reloadDailyRecipe() {
    setState(new HomeViewModelState(_state));
    connect(_databaseHandler->getDailyRecipe(), &RecipesReply::receive, this, &HomeViewModel::receiveDailyRecipe);
}

void HomeViewModel::reloadBreakfastRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast));
    connect(_databaseHandler->getHomepageCollection("breakfast"), &RecipesReply::receive,
            this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::reloadDrinkRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink));
    connect(_databaseHandler->getHomepageCollection("drink"), &RecipesReply::receive,
            this, &HomeViewModel::receiveDrinkRecipes);
}

void HomeViewModel::reloadRecipesForBigGroup() {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup));
    connect(_databaseHandler->getHomepageCollection("forBigGroup"), &RecipesReply::receive,
            this, &HomeViewModel::receiveRecipesForBigGroup);
}

void HomeViewModel::reloadLowCalorieRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie));
    connect(_databaseHandler->getHomepageCollection("lowCalorie"), &RecipesReply::receive,
            this, &HomeViewModel::receiveLowCalorieRecipes);
}

HomeViewModelState *HomeViewModel::getState() const {
    return _state;
}

void HomeViewModel::setState(HomeViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}

void HomeViewModel::receiveDailyRecipe(RecipesReply *recipeReply, QList<Recipe*> recipe) {
    setState(new HomeViewModelState(_state, recipe[0]));
    recipeReply->deleteLater();
}

void HomeViewModel::receiveBreakfastRecipes(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast, recipes));
    recipesReply->deleteLater();
}

void HomeViewModel::receiveDrinkRecipes(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink, recipes));
    recipesReply->deleteLater();
}

void HomeViewModel::receiveRecipesForBigGroup(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup, recipes));
    recipesReply->deleteLater();
}

void HomeViewModel::receiveLowCalorieRecipes(RecipesReply *recipesReply, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie, recipes));
    recipesReply->deleteLater();
}
