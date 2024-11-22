#include "RecipesReplay.h"
#include <QJsonArray>
#include <QDebug>

RecipesReplay::RecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : QObject(parent),
      _url(url),
      _networkManager(networkManager),
      _loudsNumber(loudsNumber),
      _networkReplay(_networkManager->get(QNetworkRequest(url)))
{
    qDebug() << 4;
    connect(_networkReplay, &QNetworkReply::readyRead, this, &RecipesReplay::processResponse);
    _networkReplay->setParent(this);
}

void RecipesReplay::sendResponse(QList<QJsonObject> &recipes) {
    qDebug() << 6;
    QList<Recipe*> processedRecipes;
    processedRecipes.reserve(recipes.size());
    for (auto &recipe: recipes) {
        if (recipe.size() >= 6) {
            int id = recipe.value("id").toInt();
            QString name = recipe.value("name").toString();
            QString image = recipe.value("image").toString();
            QList<QString> categories;
            for (auto category: recipe.value("categories").toArray())
                categories.append(category.toString());
            int servingsNumber = recipe.value("amountOfServings").toInt();
            QList<Recipe::InstructionRecord> instructions;
            for (auto instruction: recipe.value("instructions").toArray()) {
                auto instructionObject = instruction.toObject();
                QList<QPair<int, int>> timers;
                for (auto timer: instructionObject.value("timers").toArray()) {
                    auto timerObject = timer.toObject();
                    timers.append({ timerObject.value("num1").toInt(), timerObject.value("num2").toInt() });
                }
                instructions.append({ instructionObject.value("instruction").toString(), timers });
            }
            processedRecipes.append(new Recipe(id, name, image, categories, servingsNumber, instructions));
        }
        else if (recipe.contains("id")) {
            processedRecipes.append(new Recipe(recipe.value("id").toInt()));
        }
        else {
            processedRecipes.append(new Recipe());
        }
    }
    emit receive(this, processedRecipes);
}

void RecipesReplay::reload() {
    qDebug() << 6.5;
    _networkReplay = _networkManager->get(QNetworkRequest(_url));
    connect(_networkReplay, &QNetworkReply::readyRead, this, &RecipesReplay::processResponse);
}
