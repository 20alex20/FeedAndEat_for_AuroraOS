#include "DailyRecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDate>
#include <QDebug>
#include "RecipeReplay.h"

DailyRecipeReplay::DailyRecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void DailyRecipeReplay::processResponse() {
    qDebug() << 5;
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonParseError).object();
    _networkReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        auto recipeIds = obj.value(obj.keys().at(0)).toObject().value("recipesId").toArray();
        int recipeId = recipeIds[QDate::currentDate().year() % recipeIds.size()].toInt();
        auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
        auto newRecipesReplay = new RecipeReplay(QUrl(url), _networkManager, recipeId, this);
        connect(newRecipesReplay, &RecipeReplay::receive, this, &DailyRecipeReplay::receive);
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void DailyRecipeReplay::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    qDebug() << "a5.1";
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { new Recipe() });
    else
        reload();
}
