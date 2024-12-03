#include "RecipesReply.h"
#include <QJsonArray>

RecipesReply::RecipesReply(QObject *parent)
    : QObject(parent),
      _url(""),
      _networkManager(nullptr),
      _networkReply(nullptr),
      _loudsNumber(0)
{ }

RecipesReply::RecipesReply(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
    : QObject(parent),
      _url(url),
      _networkManager(networkManager),
      _networkReply(_networkManager->get(QNetworkRequest(url))),
      _loudsNumber(loudsNumber)
{
    connect(_networkReply, &QNetworkReply::readyRead, this, &RecipesReply::processResponse);
    connect(_networkReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &RecipesReply::processError);
    _networkReply->setParent(this);
}

QString RecipesReply::getUrl() {
    return _url.toString();
}

void RecipesReply::sendResponse(QList<QJsonObject> &recipes) {
    QList<Recipe*> processedRecipes;
    processedRecipes.reserve(recipes.size());
    for (auto &recipe: recipes) {
        if (recipe.size() >= 6) {
            int id = recipe.value("id").toInt();
            QString name = recipe.value("name").toString();
            QString image = recipe.value("image").toString();
            QList<QString> categories;
            auto categoriesArray = recipe.value("categories").toArray();
            categories.reserve(categoriesArray.size());
            for (auto category: categoriesArray)
                categories.append(category.toString());
            int servingsNumber = recipe.value("amountOfServings").toInt();
            QList<QString> instructions;
            QList<QList<QPair<int, int>>> instructionsTimers;
            auto fullInstructions = recipe.value("instructions").toArray();
            instructions.reserve(fullInstructions.size());
            instructionsTimers.reserve(fullInstructions.size());
            for (auto fullInstruction: fullInstructions) {
                auto fullInstructionObject = fullInstruction.toObject();
                instructions.append(fullInstructionObject.value("instruction").toString());
                instructionsTimers.append(QList<QPair<int, int>>());
                auto timers = fullInstructionObject.value("timers").toArray();
                auto &instructionTimers = instructionsTimers.last();
                instructionTimers.reserve(timers.size());
                for (auto timer: timers) {
                    auto timerObject = timer.toObject();
                    instructionTimers.append({ timerObject.value("num1").toInt(), timerObject.value("num2").toInt() });
                }
            }
            processedRecipes.append(new Recipe(id, name, image, categories, servingsNumber, instructions, instructionsTimers));
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

void RecipesReply::reload() {
    _networkReply = _networkManager->get(QNetworkRequest(_url));
    connect(_networkReply, &QNetworkReply::readyRead, this, &RecipesReply::processResponse);
    connect(_networkReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &RecipesReply::processError);
    _networkReply->setParent(this);
}
