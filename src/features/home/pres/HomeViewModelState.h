#ifndef HOMEVIEWMODELSTATE_H
#define HOMEVIEWMODELSTATE_H

#include <QObject>
#include <QVariantList>
#include "src/features/database/domain/Recipe.h"

class HomeViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Recipe *dailyRecipe READ getDailyRecipe CONSTANT)
    Q_PROPERTY(QVariantList breakfastRecipes READ getBreakfastRecipes CONSTANT)
    Q_PROPERTY(Status breakfastRecipesStatus READ getBreakfastRecipesStatus CONSTANT)
    Q_PROPERTY(QVariantList drinkRecipes READ getDrinkRecipes CONSTANT)
    Q_PROPERTY(Status drinkRecipesStatus READ getDrinkRecipesStatus CONSTANT)
    Q_PROPERTY(QVariantList recipesForBigGroup READ getRecipesForBigGroup CONSTANT)
    Q_PROPERTY(Status recipesForBigGroupStatus READ getRecipesForBigGroupStatus CONSTANT)
    Q_PROPERTY(QVariantList lowCalorieRecipes READ getLowCalorieRecipes CONSTANT)
    Q_PROPERTY(Status lowCalorieRecipeStatus READ getLowCalorieRecipesStatus CONSTANT)
public:
    enum Collection {
        Breakfast = Qt::UserRole + 1,
        Drink,
        ForBigGroup,
        LowCalorie
    };
    Q_ENUM(Collection)
    enum Status {
        Loading,
        Success,
        Error
    };
    Q_ENUM(Status)

    explicit HomeViewModelState(QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Recipe *dailyRecipe, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Collection collection, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Collection collection, QList<Recipe*> &recipes, QObject *parent = nullptr);

    Recipe *getDailyRecipe();
    QVariantList getVariantList(HomeViewModelState::Collection collection);
    QVariantList getBreakfastRecipes();
    Status getBreakfastRecipesStatus();
    QVariantList getDrinkRecipes();
    Status getDrinkRecipesStatus();
    QVariantList getRecipesForBigGroup();
    Status getRecipesForBigGroupStatus();
    QVariantList getLowCalorieRecipes();
    Status getLowCalorieRecipesStatus();
    QList<Recipe*> getCollectionRecipes(int index);
    Status getCollectionRecipesStatus(int index);

private:
    Recipe *_dailyRecipe;
    QList<Recipe*> _collectionsRecipes[4];
    Status _collectionsRecipesStatuses[4];
};

#endif // HOMEVIEWMODELSTATE_H
