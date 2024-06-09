#include "recipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>

RecipeReplay::RecipeReplay(const int recipeId, QNetworkReply* recipeReplay, QNetworkAccessManager *networkManager, QObject* parent):
    QObject(parent),
    _recipeId(recipeId),
    _recipeReplay(recipeReplay),
    _networkManager(networkManager)
{
    connect(_recipeReplay, &QNetworkReply::readyRead, this, &RecipeReplay::getRecipe);
}

void RecipeReplay::getRecipe() {
    QJsonParseError jsonRarseError;
    auto recipe = QJsonDocument::fromJson(_recipeReplay->readAll(), &jsonRarseError).object();
    _recipeReplay->deleteLater();

    if (jsonRarseError.error != QJsonParseError::NoError || recipe.contains("error")) {
        auto recipeReplay = _networkManager->get(QNetworkRequest(_recipeReplay->url()));
        auto newRecipeReplay = new RecipeReplay(_recipeId, recipeReplay, _networkManager);
        connect(newRecipeReplay, &RecipeReplay::receive, this, &RecipeReplay::receive);
    }
    else {
        emit receive(_recipeId, recipe.value(QString::number(_recipeId)).toObject());
        this->deleteLater();
    }
}
