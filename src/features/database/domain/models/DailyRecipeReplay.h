#ifndef DAILYRECIPEREPLAY_H
#define DAILYRECIPEREPLAY_H

#include "RecipesReplay.h"
#include "src/features/Default.h"

class DailyRecipeReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit DailyRecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void receiveRecipes() override;
};

#endif // DAILYRECIPEREPLAY_H
