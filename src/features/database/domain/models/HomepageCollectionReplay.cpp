#include "HomepageCollectionReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

HomepageCollectionReplay::HomepageCollectionReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void HomepageCollectionReplay::receiveRecipes() {
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto sth = QJsonDocument::fromJson(_recipesReplay->readAll(), &jsonParseError);
    _recipesReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !sth.object().contains("error")) {
        auto arr = sth.array();
        QList<QJsonObject> recipes;
        recipes.reserve(arr.size());
        for (auto recipe: arr)
            recipes.append(recipe.toObject());
        emit receive(recipes);
    }
    else if (_loudsNumber <= 0) {
        emit receive({ });
    }
    else {
        reload();
    }
}
