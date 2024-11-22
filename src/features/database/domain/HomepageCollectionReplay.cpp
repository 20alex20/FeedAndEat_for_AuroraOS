#include "HomepageCollectionReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

HomepageCollectionReplay::HomepageCollectionReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void HomepageCollectionReplay::processResponse() {
    qDebug() << "a5";
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto sth = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonParseError);
    _networkReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !sth.object().contains("error")) {
        auto arr = sth.array();
        QList<QJsonObject> recipes;
        recipes.reserve(arr.size());
        for (auto recipe: arr)
            recipes.append(recipe.toObject());
        sendResponse(recipes);
    }
    else if (_loudsNumber <= 0) {
        emit receive(this, { });
    }
    else {
        reload();
    }
}
