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

    void receiveDailyRecipe(RecipesReplay *recipeReplay, QList<Recipe*> recipe);
    void receiveBreakfastRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes);
    void receiveDrinkRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes);
    void receiveRecipesForBigGroup(RecipesReplay *recipesReplay, QList<Recipe*> recipes);
    void receiveLowCalorieRecipes(RecipesReplay *recipesReplay, QList<Recipe*> recipes);

    void setState(HomeViewModelState* newState);
    HomeViewModelState *getState() const;
signals:
    void stateChanged();

private:
    DatabaseHandler * const _databaseHandler;
    HomeViewModelState *_state;
};

#endif // HOMEPAGEVIEWMODEL_H
