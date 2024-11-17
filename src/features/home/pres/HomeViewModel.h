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
    explicit HomeViewModel(DatabaseHandler *databaseHandler, QObject *parent = nullptr);

    Q_INVOKABLE void bind();

    void receiveDailyRecipe(QList<QJsonObject> recipe);
    void receiveRecipesOfBreakfast(QList<QJsonObject> recipe);
    void receiveRecipesOfDrink(QList<QJsonObject> recipe);
    void receiveRecipesOfForBigGroup(QList<QJsonObject> recipe);
    void receiveRecipesOfLowCalorie(QList<QJsonObject> recipe);

signals:
    void dailyRecipeChanged();
    void recipesOfBreakfastChanged();
    void recipesOfDrinkChanged();
    void recipesOfForBigGroupChanged();
    void recipesOfLowCalorieChanged();

private:
    QVariantMap _dailyRecipe;
    QString _recipesOfBreakfast;
    QString _recipesOfDrink;
    QString _recipesOfForBigGroup;
    QString _recipesOfLowCalorie;

    QString _recipeIds;
    QList<QString> _recipe;

    DatabaseHandler *_databaseHandler;
};

#endif // HOMEPAGEVIEWMODEL_H
