#ifndef DAILYRECIPEREPLY_H
#define DAILYRECIPEREPLY_H

#include "RecipesReply.h"
#include "src/Default.h"

class DailyRecipeReply : public RecipesReply
{
    Q_OBJECT
public:
    explicit DailyRecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    virtual ~DailyRecipeReply() override;

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;
};

#endif // DAILYRECIPEREPLY_H
