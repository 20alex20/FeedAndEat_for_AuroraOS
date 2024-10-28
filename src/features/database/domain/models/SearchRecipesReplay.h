#ifndef SEARCHRECIPESREPLAY_H
#define SEARCHRECIPESREPLAY_H

#include "RecipesReplay.h"
#include "src/features/Default.h"

class SearchRecipesReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit SearchRecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void receiveRecipes() override;
    void receiveRecipe(QList<QJsonObject> recipe);

    QList<QJsonObject> _recipes;
    int _recipesCnt;
};

#endif // SEARCHRECIPESREPLAY_H
