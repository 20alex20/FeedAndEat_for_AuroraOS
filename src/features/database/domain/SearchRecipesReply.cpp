#include "SearchRecipesReply.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "RecipeReply.h"

SearchRecipesReply::SearchRecipesReply(const QUrl &url, QNetworkAccessManager * const networkManager, int loudsNumber, QObject *parent)
    : RecipesReply(url, networkManager, loudsNumber, parent),
      _withSearchQuery(url.toString().right(4) == "~%22"),
      _recipes(),
      _recipesCnt(0)
{ }

SearchRecipesReply::~SearchRecipesReply() { }

void SearchRecipesReply::processResponse() {
    QJsonParseError jsonRarseError;
    auto sth = QJsonDocument::fromJson(_networkReply->readAll(), &jsonRarseError);

    QJsonObject obj;
    if (jsonRarseError.error == QJsonParseError::NoError && sth.isObject() && !(obj = sth.object()).contains("error")) {
        if (obj.isEmpty()) {
            emit receive(this, { });
            return;
        }
        auto keys = obj.keys();
        _recipes.reserve(keys.size());
        for (int i = 0; i < keys.size(); i++) {
            int recipeId = obj.value(keys[i]).toObject().value("recipeId").toInt();
            _recipes.append(new Recipe(recipeId));
            if (!_withSearchQuery && i == Default::PageLength)
                break;
            loadRecipe(recipeId);
        }
    }
    else if (jsonRarseError.error == QJsonParseError::NoError && sth.isArray()) {
        auto arr = sth.array();
        int firstNotNull = 0;
        while (firstNotNull < arr.size()) {
            if (!arr[firstNotNull].isNull())
                break;
            firstNotNull++;
        }
        if (firstNotNull == arr.size()) {
            emit receive(this, { });
            return;
        }
        _recipes.reserve(arr.size() - firstNotNull);
        for (int i = firstNotNull; i < arr.size(); i++) {
            int recipeId = arr[i].toObject().value("recipeId").toInt();
            _recipes.append(new Recipe(recipeId));
            if (i == Default::PageLength + firstNotNull)
                break;
            loadRecipe(recipeId);
        }
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void SearchRecipesReply::processError(QNetworkReply::NetworkError code) {
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { nullptr });
    else
        reload();
}

void SearchRecipesReply::loadRecipe(int recipeId) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    auto newRecipesReply = new RecipeReply(QUrl(url), _networkManager, recipeId, this);
    connect(newRecipesReply, &RecipeReply::receive, this, &SearchRecipesReply::collectResponses);
}

void SearchRecipesReply::collectResponses(RecipesReply *recipesReply, QList<Recipe*> recipe) {
    Q_UNUSED(recipesReply)
    auto recipeId = recipe[0]->getId();
    for (int i = 0; i < _recipes.size(); i++)
        if (_recipes[i]->getId() == recipeId) {
            _recipes[i]->deleteLater();
            _recipes[i] = recipe[0];
            _recipesCnt++;
            break;
        }
    if (_recipesCnt == _recipes.size() || (!_withSearchQuery && _recipesCnt == Default::PageLength))
        emit receive(this, _recipes);
}
