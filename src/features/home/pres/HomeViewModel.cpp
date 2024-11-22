#include "HomeViewModel.h"
#include <QDebug>

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
    qDebug() << "2";
    connect(_databaseHandler->getDailyRecipe(), &RecipesReplay::receive, this, &HomeViewModel::receiveDailyRecipe);
    connect(_databaseHandler->getHomepageCollection("breakfast"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveBreakfastRecipes);
    /*connect(_databaseHandler->getHomepageCollection("drink"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveDrinkRecipes);
    connect(_databaseHandler->getHomepageCollection("forBigGroup"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveRecipesForBigGroup);
    connect(_databaseHandler->getHomepageCollection("lowCalorie"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveLowCalorieRecipes);*/
}

void HomeViewModel::reloadDailyRecipe() {
    setState(new HomeViewModelState(_state));
    connect(_databaseHandler->getDailyRecipe(), &RecipesReplay::receive, this, &HomeViewModel::receiveDailyRecipe);
}

void HomeViewModel::reloadBreakfastRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast));
    connect(_databaseHandler->getHomepageCollection("breakfast"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveBreakfastRecipes);
}

void HomeViewModel::reloadDrinkRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink));
    connect(_databaseHandler->getHomepageCollection("drink"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveDrinkRecipes);
}

void HomeViewModel::reloadRecipesForBigGroup() {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup));
    connect(_databaseHandler->getHomepageCollection("forBigGroup"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveRecipesForBigGroup);
}

void HomeViewModel::reloadLowCalorieRecipes() {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie));
    connect(_databaseHandler->getHomepageCollection("lowCalorie"), &RecipesReplay::receive,
            this, &HomeViewModel::receiveLowCalorieRecipes);
}

void HomeViewModel::receiveDailyRecipe(RecipesReplay *recipeReplay, QList<Recipe*> recipe) {
    qDebug() << 7;
    qDebug() << recipe[0]->getId() << recipe[0]->getName();
    setState(new HomeViewModelState(_state, recipe[0]));
    recipeReplay->deleteLater();
}

void HomeViewModel::receiveBreakfastRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes) {
    qDebug() << "a7";
    qDebug() << recipes.size();
    if (recipes.size() > 0)
        qDebug() << recipes[0]->getId() << recipes[0]->getName();
    setState(new HomeViewModelState(_state, HomeViewModelState::Breakfast, recipes));
    recipesReplay->deleteLater();
}

void HomeViewModel::receiveDrinkRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::Drink, recipes));
    recipesReplay->deleteLater();
}

void HomeViewModel::receiveRecipesForBigGroup(RecipesReplay *recipesReplay, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::ForBigGroup, recipes));
    recipesReplay->deleteLater();
}

void HomeViewModel::receiveLowCalorieRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes) {
    setState(new HomeViewModelState(_state, HomeViewModelState::LowCalorie, recipes));
    recipesReplay->deleteLater();
}

void HomeViewModel::setState(HomeViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}

HomeViewModelState *HomeViewModel::getState() const {
    qDebug() << "length" << _state->getCollectionRecipes(0).size();
    return _state;
}
