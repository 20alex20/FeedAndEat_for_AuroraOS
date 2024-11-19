#include "SearchRecipesReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "RecipeReplay.h"

SearchRecipesReplay::SearchRecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent),
      _recipes(),
      _recipesCnt(0)
{ }

void SearchRecipesReplay::processResponse() {
    _loudsNumber--;
    QJsonParseError jsonRarseError;
    auto obj = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonRarseError).object();
    _networkReplay->deleteLater();

    if (jsonRarseError.error == QJsonParseError::NoError && !obj.contains("error")) {
        auto keys = obj.keys();
        _recipes.reserve(keys.size());
        for (int i = 0; i < keys.size(); i++) {
            int recipeId = obj.value(keys[i]).toObject().value("recipeId").toInt();
            _recipes.append(new Recipe(recipeId));
            if (i >= Default::PageLength)
                break;
            auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
            auto newRecipesReplay = new RecipeReplay(QUrl(url), _networkManager, recipeId, this);
            connect(newRecipesReplay, &RecipeReplay::receive, this, &SearchRecipesReplay::collectResponses);
        }
    }
    else if (_loudsNumber <= 0) {
        emit receive(this, { });
    }
    else {
        reload();
    }
}

void SearchRecipesReplay::collectResponses(QList<Recipe*> recipe) {
    auto recipeId = recipe[0]->getId();
    for (int i = 0; i < _recipes.size(); i++)
        if (_recipes[i]->getId() == recipeId) {
            _recipes[i]->deleteLater();
            _recipes[i] = recipe[0];
            _recipesCnt++;
            break;
        }
    if (_recipesCnt == _recipes.size() || _recipesCnt == Default::PageLength)
        emit receive(this, _recipes);
}
