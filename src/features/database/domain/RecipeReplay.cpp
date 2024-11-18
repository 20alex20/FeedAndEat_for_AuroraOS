#include "RecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>

RecipeReplay::RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

RecipeReplay::RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, QObject *parent)
    : RecipesReplay(url, networkManager, Default::AttemptsNumber, parent)
{ }

void RecipeReplay::processResponse() {
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_recipesReplay->readAll(), &jsonParseError).object();
    _recipesReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        QList<QJsonObject> recipe = { obj.value(obj.keys().at(0)).toObject() };
        sendResponse(recipe);
    }
    else if (_loudsNumber <= 0) {
        emit receive({ new Recipe() });
    }
    else {
        reload();
    }
}
