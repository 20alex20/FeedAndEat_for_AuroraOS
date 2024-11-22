#ifndef RECIPEREPLAY_H
#define RECIPEREPLAY_H

#include "RecipesReplay.h"
#include "src/Default.h"

class RecipeReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, QObject *parent);

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;

    int _recipeId;
};

#endif // RECIPEREPLAY_H
