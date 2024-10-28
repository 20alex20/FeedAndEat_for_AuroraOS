#ifndef HOMEPAGEVIEWMODEL_H
#define HOMEPAGEVIEWMODEL_H

#include "src/features/databaseRepository/domain/repository/DatabaseHandler.h"

class HomePageViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString recipeOfDayOfYear READ getRecipeOfDayOfYear NOTIFY recipeOfDayOfYearChanged)
    Q_PROPERTY(QString recipesOfBreakfast READ getRecipesOfBreakfast NOTIFY recipesOfBreakfastChanged)
    Q_PROPERTY(QString recipesOfDrink READ getRecipesOfDrink NOTIFY recipesOfDrinkChanged)
    Q_PROPERTY(QString recipesOfForBigGroup READ getRecipesOfForBigGroup NOTIFY recipesOfForBigGroupChanged)
    Q_PROPERTY(QString recipesOfLowCalorie READ getRecipesOfLowCalorie NOTIFY recipesOfLowCalorieChanged)

    Q_PROPERTY(QString recipeIds READ getRecipeIds NOTIFY recipeIdsChanged)
    Q_PROPERTY(QString recipe READ getRecipe NOTIFY recipeChanged)
public:
    explicit HomePageViewModel(QObject *parent = nullptr);
    explicit HomePageViewModel(DatabaseHandler *databaseHandler, QObject *parent = nullptr);

    Q_INVOKABLE void bind();

    void receiveRecipeIdOfDayOfYear(const int recipeId);
    void receiveRecipeOfDayOfYear(const int recipeId, QJsonObject recipe);
    QString getRecipeOfDayOfYear();
    void receiveRecipesOfHomepageCollection(QString &collectionName, QList<QJsonObject> recipes);
    QString getRecipesOfBreakfast();
    QString getRecipesOfDrink();
    QString getRecipesOfForBigGroup();
    QString getRecipesOfLowCalorie();

    void receiveRecipeIds(QList<int> recipeIds);
    QString getRecipeIds();
    void receiveRecipe(const int recipeId, QJsonObject recipe);
    QString getRecipe();

signals:
    void recipeOfDayOfYearChanged();
    void recipesOfBreakfastChanged();
    void recipesOfDrinkChanged();
    void recipesOfForBigGroupChanged();
    void recipesOfLowCalorieChanged();

    void recipeIdsChanged();
    void recipeChanged();

private:
    QString _recipeOfDayOfYear;
    QString _recipesOfBreakfast;
    QString _recipesOfDrink;
    QString _recipesOfForBigGroup;
    QString _recipesOfLowCalorie;

    QString _recipeIds;
    QList<QString> _recipe;

    DatabaseHandler *_databaseHandler;
};

#endif // HOMEPAGEVIEWMODEL_H
