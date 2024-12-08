#include "DailyRecipeReply.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDate>
#include "RecipeReply.h"

DailyRecipeReply::DailyRecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, int loudsNumber, QObject *parent)
    : RecipesReply(url, networkManager, loudsNumber, parent)
{ }

DailyRecipeReply::~DailyRecipeReply() { }

void DailyRecipeReply::processResponse() {
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_networkReply->readAll(), &jsonParseError).object();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        auto recipeIds = obj.value(obj.keys().at(0)).toObject().value("recipesId").toArray();
        int recipeId = recipeIds[QDate::currentDate().year() % recipeIds.size()].toInt();
        auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
        auto newRecipesReply = new RecipeReply(QUrl(url), _networkManager, recipeId, this);
        connect(newRecipesReply, &RecipeReply::receive, this, &DailyRecipeReply::receive);
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void DailyRecipeReply::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { new Recipe() });
    else
        reload();
}
