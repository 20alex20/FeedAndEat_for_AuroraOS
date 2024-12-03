#include "HomepageCollectionReply.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

HomepageCollectionReply::HomepageCollectionReply(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReply(url, networkManager, loudsNumber, parent)
{ }

HomepageCollectionReply::~HomepageCollectionReply() { }

void HomepageCollectionReply::processResponse() {
    QJsonParseError jsonParseError;
    auto sth = QJsonDocument::fromJson(_networkReply->readAll(), &jsonParseError);

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

void HomepageCollectionReply::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { });
    else
        reload();
}
