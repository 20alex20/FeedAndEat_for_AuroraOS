#ifndef SEARCHRECIPESREPLAY_H
#define SEARCHRECIPESREPLAY_H

#include "RecipesReplay.h"
#include "src/Default.h"

class SearchRecipesReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit SearchRecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void processResponse() override;
    void collectResponses(QList<Recipe*> recipe);

    QList<Recipe*> _recipes;
    int _recipesCnt;
};

#endif // SEARCHRECIPESREPLAY_H
