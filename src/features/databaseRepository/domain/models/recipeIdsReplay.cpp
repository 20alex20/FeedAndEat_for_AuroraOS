#include "recipeIdsReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

RecipeIdsReplay::RecipeIdsReplay(QNetworkReply* recipeIdsReplay, QNetworkAccessManager *networkManager, QObject* parent):
    QObject(parent),
    _recipeIdsReplay(recipeIdsReplay),
    _networkManager(networkManager)
{
    connect(recipeIdsReplay, &QNetworkReply::readyRead, this, &RecipeIdsReplay::getRecipeIds);
}

void RecipeIdsReplay::getRecipeIds() {
    auto url = _recipeIdsReplay->url();
    QJsonParseError jsonRarseError;
    auto recipeIds = QJsonDocument::fromJson(_recipeIdsReplay->readAll(), &jsonRarseError).object();
    _recipeIdsReplay->deleteLater();

    if (jsonRarseError.error != QJsonParseError::NoError || recipeIds.contains("error")) {
        auto recipeIdsReplay = _networkManager->get(QNetworkRequest(url));
        auto newRecipeIdsReplay = new RecipeIdsReplay(recipeIdsReplay, _networkManager);
        connect(newRecipeIdsReplay, &RecipeIdsReplay::receive, this, &RecipeIdsReplay::receive);
    }
    else {
        QList<int> result;
        auto keysList = recipeIds.keys();
        for (auto i = 0; i < keysList.size(); i++)
            result.append(recipeIds.value(keysList[i]).toObject().value("recipeId").toInt());
        emit receive(result);
        this->deleteLater();
    }
}
