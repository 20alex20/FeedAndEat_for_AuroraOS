#include "RecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>

RecipeReplay::RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent),
      _recipeId(recipeId)
{ }

RecipeReplay::RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, QObject *parent)
    : RecipeReplay(url, networkManager, recipeId, Default::AttemptsNumber, parent)
{ }

void RecipeReplay::processResponse() {
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonParseError).object();
    _networkReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        QList<QJsonObject> recipe = { obj.value(obj.keys().at(0)).toObject() };
        sendResponse(recipe);
    }
    else if (_loudsNumber <= 0) {
        emit receive(this, { new Recipe(_recipeId) });
    }
    else {
        reload();
    }
}
