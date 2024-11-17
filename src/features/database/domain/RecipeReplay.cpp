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
        sendResponse({ obj.value(obj.keys().at(0)).toObject() });
    }
    else if (_loudsNumber <= 0) {
        sendResponse({ QJsonObject() });
    }
    else {
        reload();
    }
}
