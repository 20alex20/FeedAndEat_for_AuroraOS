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
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonParseError).object();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        QList<QJsonObject> recipe = { obj.value(obj.keys().at(0)).toObject() };
        sendResponse(recipe);
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void RecipeReplay::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { new Recipe(_recipeId) });
    else
        reload();
}
