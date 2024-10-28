#include "RecipeReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>

RecipeReplay::RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject* parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent)
{ }

void RecipeReplay::receiveRecipes() {
    _loudsNumber--;
    QJsonParseError jsonParseError;
    auto obj = QJsonDocument::fromJson(_recipesReplay->readAll(), &jsonParseError).object();
    _recipesReplay->deleteLater();

    if (jsonParseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        emit receive({ obj.value(obj.keys().at(0)).toObject() });
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
