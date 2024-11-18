#include "HomeViewModel.h"

HomeViewModel::HomeViewModel(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr),
      _state(new HomeViewModelState()),
      _dailyRecipeReplay(nullptr),
      _breakfastRecipesReplay(nullptr),
      _drinkRecipesReplay(nullptr),
      _recipesForBigGroupReplay(nullptr),
      _lowCalorieRecipesReplay(nullptr)
{ }

HomeViewModel::HomeViewModel(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler),
      _state(new HomeViewModelState()),
      _dailyRecipeReplay(nullptr),
      _breakfastRecipesReplay(nullptr),
      _drinkRecipesReplay(nullptr),
      _recipesForBigGroupReplay(nullptr),
      _lowCalorieRecipesReplay(nullptr)
{ }

HomeViewModel::~HomeViewModel() {
    _state->deleteLater();
}

void HomeViewModel::bind() {
    connect(_dailyRecipeReplay = _databaseHandler->getDailyRecipe(),
            &RecipesReplay::receive, this, &HomeViewModel::receiveDailyRecipe);
    connect(_breakfastRecipesReplay = _databaseHandler->getHomepageCollection("breakfast"),
            &RecipesReplay::receive, this, &HomeViewModel::receiveBreakfastRecipes);
    connect(_drinkRecipesReplay = _databaseHandler->getHomepageCollection("drink"),
            &RecipesReplay::receive, this, &HomeViewModel::receiveDrinkRecipes);
    connect(_recipesForBigGroupReplay = _databaseHandler->getHomepageCollection("forBigGroup"),
            &RecipesReplay::receive, this, &HomeViewModel::receiveRecipesForBigGroup);
    connect(_lowCalorieRecipesReplay = _databaseHandler->getHomepageCollection("lowCalorie"),
            &RecipesReplay::receive, this, &HomeViewModel::receiveLowCalorieRecipes);
}

void HomeViewModel::reloadDailyRecipe() {
    setState(new HomeViewModelState(_state));
    _dailyRecipeReplay = _databaseHandler->getDailyRecipe();
    connect(_dailyRecipeReplay, &RecipesReplay::receive, this, &HomeViewModel::receiveDailyRecipe);
}

void HomeViewModel::reloadBreakfastRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast));
    auto _breakfastRecipesReplay = _databaseHandler->getHomepageCollection("breakfast");
    connect(_breakfastRecipesReplay, &RecipesReplay::receive, this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::reloadDrinkRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink));
    auto _dailyRecipeReplay = _databaseHandler->getHomepageCollection("drink");
    connect(_dailyRecipeReplay, &RecipesReplay::receive, this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::reloadRecipesForBigGroup() {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup));
    auto _recipesForBigGroupReplay = _databaseHandler->getHomepageCollection("forBigGroup");
    connect(_recipesForBigGroupReplay, &RecipesReplay::receive, this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::reloadLowCalorieRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie));
    auto _lowCalorieRecipesReplay = _databaseHandler->getHomepageCollection("lowCalorie");
    connect(_lowCalorieRecipesReplay, &RecipesReplay::receive, this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::receiveDailyRecipe(QList<Recipe*> recipe) {
    setState(new HomeViewModelState(_state, recipe[0]));
    _dailyRecipeReplay->deleteLater();
}

void HomeViewModel::receiveBreakfastRecipes(QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast, recipes));
    _breakfastRecipesReplay->deleteLater();
}

void HomeViewModel::receiveDrinkRecipes(QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink, recipes));
    _breakfastRecipesReplay->deleteLater();
}

void HomeViewModel::receiveRecipesForBigGroup(QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup, recipes));
    _breakfastRecipesReplay->deleteLater();
}

void HomeViewModel::receiveLowCalorieRecipes(QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie, recipes));
    _breakfastRecipesReplay->deleteLater();
}

void HomeViewModel::setState(HomeViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}

HomeViewModelState *HomeViewModel::getState() const {
    return _state;
}
