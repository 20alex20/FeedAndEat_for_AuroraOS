#ifndef HOMEPAGECOLLECTIONREPLAY_H
#define HOMEPAGECOLLECTIONREPLAY_H

#include "RecipesReplay.h"
#include "src/Default.h"

class HomepageCollectionReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit HomepageCollectionReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;
};

#endif // RECIPESOFHOMEPAGECOLLECTIONREPLAY_H
