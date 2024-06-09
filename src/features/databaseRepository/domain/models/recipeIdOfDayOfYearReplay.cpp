#include "recipeIdOfDayOfYearReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDate>

RecipeIdOfDayOfYearReplay::RecipeIdOfDayOfYearReplay(QNetworkReply* recipeIdReplay, QNetworkAccessManager *networkManager, QObject* parent):
    QObject(parent),
    _recipeIdReplay(recipeIdReplay),
    _networkManager(networkManager)
{
    connect(_recipeIdReplay, &QNetworkReply::readyRead, this, &RecipeIdOfDayOfYearReplay::getRecipeId);
}

void RecipeIdOfDayOfYearReplay::getRecipeId() {
    QJsonParseError jsonRarseError;
    auto recipeId = QJsonDocument::fromJson(_recipeIdReplay->readAll(), &jsonRarseError).object();
    _recipeIdReplay->deleteLater();

    if (jsonRarseError.error != QJsonParseError::NoError || recipeId.contains("error")) {
        auto recipeIdReplay = _networkManager->get(QNetworkRequest(_recipeIdReplay->url()));
        auto newRecipeIdReplay = new RecipeIdOfDayOfYearReplay(recipeIdReplay, _networkManager);
        connect(newRecipeIdReplay, &RecipeIdOfDayOfYearReplay::receive, this, &RecipeIdOfDayOfYearReplay::receive);
    }
    else {
        auto recipeIdsObject = recipeId.value(QString::number(QDate::currentDate().dayOfYear() - 1)).toObject();
        auto recipeIds = recipeIdsObject.toVariantMap()["recipesId"].toList();
        int index = QDate::currentDate().year() % recipeIds.size();
        emit receive(recipeIds[index].toInt());
        this->deleteLater();
    }
}
