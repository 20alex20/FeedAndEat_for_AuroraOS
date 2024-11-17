#ifndef DAILYRECIPEREPLAY_H
#define DAILYRECIPEREPLAY_H

#include "RecipesReplay.h"
#include "src/Default.h"

class DailyRecipeReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit DailyRecipeReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void processResponse() override;
};

#endif // DAILYRECIPEREPLAY_H
