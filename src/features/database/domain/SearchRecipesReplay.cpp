#include "SearchRecipesReplay.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include "RecipeReplay.h"
#include <QDebug>

SearchRecipesReplay::SearchRecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : RecipesReplay(url, networkManager, loudsNumber, parent),
      _recipes(),
      _recipesCnt(0)
{ }

void SearchRecipesReplay::processResponse() {
    qDebug() << "b4";
    QJsonParseError jsonRarseError;
    auto sth = QJsonDocument::fromJson(_networkReplay->readAll(), &jsonRarseError);

    qDebug() << _url;
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
            if (i < Default::PageLength)
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
            qDebug() << recipeId;
            _recipes.append(new Recipe(recipeId));
            if (i < Default::PageLength + firstNotNull)
                loadRecipe(recipeId);
        }
    }
    else {
        processError(QNetworkReply::ContentNotFoundError);
    }
}

void SearchRecipesReplay::processError(QNetworkReply::NetworkError code) {
    qDebug() << "b5";
    Q_UNUSED(code)
    _loudsNumber--;
    if (_loudsNumber <= 0)
        emit receive(this, { nullptr });
    else
        reload();
}

void SearchRecipesReplay::loadRecipe(int recipeId) {
    auto url = "https://feedandeat-2024-default-rtdb.firebaseio.com/recipe.json?orderBy=\"id\"&equalTo=" + QString::number(recipeId);
    auto newRecipesReplay = new RecipeReplay(QUrl(url), _networkManager, recipeId, this);
    connect(newRecipesReplay, &RecipeReplay::receive, this, &SearchRecipesReplay::collectResponses);
}

void SearchRecipesReplay::collectResponses(RecipesReplay *recipesReplay, QList<Recipe*> recipe) {
    Q_UNUSED(recipesReplay)
    qDebug() << "b8";
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
