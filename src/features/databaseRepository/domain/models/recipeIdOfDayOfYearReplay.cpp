#include "recipeIdOfDayOfYearReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>

RecipeIdOfDayOfYearReplay::RecipeIdOfDayOfYearReplay(QNetworkReply* recipeIdReplay, QNetworkAccessManager *networkManager, QObject* parent):
    QObject(parent),
    _recipeIdReplay(recipeIdReplay),
    _networkManager(networkManager)
{
    connect(_recipeIdReplay, &QNetworkReply::readyRead, this, &RecipeIdOfDayOfYearReplay::getRecipeId);
}

void RecipeIdOfDayOfYearReplay::getRecipeId() {
    auto url = _recipeIdReplay->url();
    QJsonParseError jsonRarseError;
    auto recipeId = QJsonDocument::fromJson(_recipeIdReplay->readAll(), &jsonRarseError).object();
    _recipeIdReplay->deleteLater();

    if (jsonRarseError.error != QJsonParseError::NoError || recipeId.contains("error")) {
        auto recipeIdReplay = _networkManager->get(QNetworkRequest(url));
        auto newRecipeIdReplay = new RecipeIdOfDayOfYearReplay(recipeIdReplay, _networkManager);
        connect(newRecipeIdReplay, &RecipeIdOfDayOfYearReplay::receive, this, &RecipeIdOfDayOfYearReplay::receive);
    }
    else {
        auto recipeIdsObject = recipeId.value(recipeId.keys()[0]).toObject();
        auto recipeIds = recipeIdsObject.value("recipesId").toArray();
        int index = QDate::currentDate().year() % recipeIds.size();
        emit receive(recipeIds[index].toInt());
        this->deleteLater();
    }
}
