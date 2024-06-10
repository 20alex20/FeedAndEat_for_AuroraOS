#include "recipesOfHomepageCollectionReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

RecipesOfHomepageCollectionReplay::RecipesOfHomepageCollectionReplay(QString &collectionName, QNetworkReply* recipesReplay, QNetworkAccessManager *networkManager, QObject* parent):
    QObject(parent),
    _collectionName(collectionName),
    _recipesReplay(recipesReplay),
    _networkManager(networkManager)
{
    connect(_recipesReplay, &QNetworkReply::readyRead, this, &RecipesOfHomepageCollectionReplay::getRecipes);
}

void RecipesOfHomepageCollectionReplay::getRecipes() {
    auto url = _recipesReplay->url();
    QJsonParseError jsonRarseError;
    auto recipes = QJsonDocument::fromJson(_recipesReplay->readAll(), &jsonRarseError);
    _recipesReplay->deleteLater();

    if (jsonRarseError.error != QJsonParseError::NoError || recipes.object().contains("error")) {
        auto recipesReplay = _networkManager->get(QNetworkRequest(url));
        auto newRecipesReplay = new RecipesOfHomepageCollectionReplay(_collectionName, recipesReplay, _networkManager);
        connect(newRecipesReplay, &RecipesOfHomepageCollectionReplay::receive, this, &RecipesOfHomepageCollectionReplay::receive);
    }
    else {
        auto recipesArray = recipes.array();
        QList<QJsonObject> result;
        for (auto i = 0; i < recipesArray.size(); i++)
            result.append(recipesArray[i].toObject());
        emit receive(_collectionName, result);
        this->deleteLater();
    }
}
