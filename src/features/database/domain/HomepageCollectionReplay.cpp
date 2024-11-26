#include "HomepageCollectionReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

HomepageCollectionReplay::HomepageCollectionReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void HomepageCollectionReplay::processResponse() {
    qDebug() << "a5";
    QJsonParseError jsonParseError;
    auto sth = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonParseError);

    if (jsonParseError.error == QJsonParseError::NoError && !sth.object().contains("error")) {
        auto arr = sth.array();
        QList<QJsonObject> recipes;
        recipes.reserve(arr.size());
        for (auto recipe: arr)
            recipes.append(recipe.toObject());
        sendResponse(recipes);
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void HomepageCollectionReplay::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    qDebug() << "a5.1";
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { });
    else
        reload();
}
