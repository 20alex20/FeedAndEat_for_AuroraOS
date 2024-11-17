#ifndef HOMEVIEWMODELSTATE_H
#define HOMEVIEWMODELSTATE_H

#include <QObject>
#include "src/features/database/domain/Recipe.h"

class HomeViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Recipe dailyRecipe READ getDailyRecipe CONSTANT)
    Q_PROPERTY(QList<Recipe> dailyRecipe READ getBreakfastRecipes CONSTANT)
    Q_PROPERTY(QList<Recipe> dailyRecipe READ getDrinkRecipes CONSTANT)
    Q_PROPERTY(QList<Recipe> dailyRecipe READ getRecipesForBigGroup CONSTANT)
    Q_PROPERTY(QList<Recipe> dailyRecipe READ getLowCalorieRecipes CONSTANT)
public:
    explicit HomeViewModelState(QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Recipe &dailyRecipe, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, QString collectionName, QList<Recipe> &recipes, QObject *parent = nullptr);

    Recipe getDailyRecipe();
    QList<Recipe> getBreakfastRecipes();
    QList<Recipe> getDrinkRecipes();
    QList<Recipe> getRecipesForBigGroup();
    QList<Recipe> getLowCalorieRecipes();

private:
    Recipe _dailyRecipe;
    QList<Recipe> _breakfastRecipes;
    QList<Recipe> _drinkRecipes;
    QList<Recipe> _recipesForBigGroup;
    QList<Recipe> _lowCalorieRecipes;
};

#endif // HOMEVIEWMODELSTATE_H
