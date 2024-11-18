#include "DailyRecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDate>
#include "RecipeReplay.h"

DailyRecipeReplay::DailyRecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void DailyRecipeReplay::processResponse() {
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_recipesReplay->readAll(), &jsonParseError).object();
    _recipesReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        auto recipeIds = obj.value(obj.keys().at(0)).toObject().value("recipesId").toArray();
        int index = QDate::currentDate().year() % recipeIds.size();
        auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" +
                QString::number(recipeIds[index].toInt());
        auto newRecipesReplay = new RecipeReplay(QUrl(url), _networkManager, this);
        connect(newRecipesReplay, &RecipeReplay::receive, this, &DailyRecipeReplay::receive);
    }
    else if (_loudsNumber <= 0) {
        emit receive({ new Recipe() });
    }
    else {
        reload();
    }
}
