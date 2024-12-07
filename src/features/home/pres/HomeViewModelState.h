#ifndef HOMEVIEWMODELSTATE_H
#define HOMEVIEWMODELSTATE_H

#include <QObject>
#include <QVariantList>
#include "src/features/database/domain/Recipe.h"

class HomeViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Recipe *dailyRecipe READ getDailyRecipe CONSTANT)
public:
    enum Status {
        Loading = Qt::UserRole + 1,
        Success,
        Error
    };
    Q_ENUM(Status)
    enum Collection {
        Breakfast = Qt::UserRole + 1,
        Drink,
        ForBigGroup,
        LowCalorie
    };
    Q_ENUM(Collection)

    explicit HomeViewModelState(QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Recipe *dailyRecipe, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Collection collection, QObject *parent = nullptr);
    explicit HomeViewModelState(HomeViewModelState *oldState, Collection collection, QList<Recipe*> &recipes, QObject *parent = nullptr);

    Recipe *getDailyRecipe() const;
    Q_INVOKABLE QVariantList getCollectionRecipes(HomeViewModelState::Collection collection) const;
    Q_INVOKABLE Status getCollectionStatus(HomeViewModelState::Collection collection) const;
    Q_INVOKABLE Recipe *getRecipe(HomeViewModelState::Collection collection, int index);

    QList<Recipe*> getCollectionRecipesList(int index) const;
    Status getCollectionRecipesStatus(int index) const;

private:
    Recipe *_dailyRecipe;
    QList<Recipe*> _collectionsRecipes[4];
    Status _collectionsRecipesStatuses[4];
};

#endif // HOMEVIEWMODELSTATE_H
