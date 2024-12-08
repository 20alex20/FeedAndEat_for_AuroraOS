#include "RecipeReply.h"
#include <QJsonDocument>
#include <QJsonParseError>

RecipeReply::RecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, int loudsNumber, QObject* parent)
    : RecipesReply(url, networkManager, loudsNumber, parent),
      _recipeId(recipeId)
{ }

RecipeReply::RecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, QObject *parent)
    : RecipeReply(url, networkManager, recipeId, Default::AttemptsNumber, parent)
{ }

RecipeReply::~RecipeReply() { }

void RecipeReply::processResponse() {
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_networkReply->readAll(), &jsonParseError).object();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        QList<QJsonObject> recipe = { obj.value(obj.keys().at(0)).toObject() };
        sendResponse(recipe);
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void RecipeReply::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { new Recipe(_recipeId) });
    else
        reload();
}
