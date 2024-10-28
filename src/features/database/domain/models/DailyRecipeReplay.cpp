#include "DailyRecipeReplay.h"
#include "RecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDate>

DailyRecipeReplay::DailyRecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void DailyRecipeReplay::receiveRecipes() {
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
        emit receive({ QJsonValue("{"
                       "\"id\": -1,"
                       "\"name\": \"Loading error\","
                       "\"image\": \"https://dummyimage.com/400x300/99cccc.jpg&text=Click+to+reload\","
                       "\"amountOfServings\": 0,"
                       "\"instructions\": []"
                       "}").toObject() });
    }
    else {
        reload();
    }
}
