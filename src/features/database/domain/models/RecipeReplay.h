#ifndef RECIPEREPLAY_H
#define RECIPEREPLAY_H

#include "RecipesReplay.h"
#include "src/features/Default.h"

class RecipeReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, QObject *parent)
        : RecipeReplay(url, networkManager, Default::AttemptsNumber, parent)
    { }

private:
    void receiveRecipes() override;
};

#endif // RECIPEREPLAY_H
