#ifndef RECIPEREPLAY_H
#define RECIPEREPLAY_H

#include "RecipesReplay.h"
#include "src/Default.h"

class RecipeReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    explicit RecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, QObject *parent);

private:
    void processResponse() override;
};

#endif // RECIPEREPLAY_H
