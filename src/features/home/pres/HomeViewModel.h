#ifndef HOMEPAGEVIEWMODEL_H
#define HOMEPAGEVIEWMODEL_H

#include "src/features/database/data/DatabaseHandler.h"
#include "HomeViewModelState.h"

class HomeViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HomeViewModelState *state READ getState NOTIFY stateChanged)
public:
    explicit HomeViewModel(QObject *parent = nullptr);
    explicit HomeViewModel(DatabaseHandler * const databaseHandler, QObject *parent = nullptr);
    ~HomeViewModel();

    Q_INVOKABLE void bind();
    Q_INVOKABLE void reloadDailyRecipe();
    Q_INVOKABLE void reloadBreakfastRecipes();
    Q_INVOKABLE void reloadDrinkRecipes();
    Q_INVOKABLE void reloadRecipesForBigGroup();
    Q_INVOKABLE void reloadLowCalorieRecipes();

    void receiveDailyRecipe(QList<Recipe*> recipe);
    void receiveBreakfastRecipes(QList<Recipe*> recipes);
    void receiveDrinkRecipes(QList<Recipe*> recipes);
    void receiveRecipesForBigGroup(QList<Recipe*> recipes);
    void receiveLowCalorieRecipes(QList<Recipe*> recipes);

    void setState(HomeViewModelState* newState);
    HomeViewModelState *getState() const;
signals:
    void stateChanged();

private:
    DatabaseHandler * const _databaseHandler;
    HomeViewModelState *_state;

    RecipesReplay *_dailyRecipeReplay;
    RecipesReplay *_breakfastRecipesReplay;
    RecipesReplay *_drinkRecipesReplay;
    RecipesReplay *_recipesForBigGroupReplay;
    RecipesReplay *_lowCalorieRecipesReplay;
};

#endif // HOMEPAGEVIEWMODEL_H
