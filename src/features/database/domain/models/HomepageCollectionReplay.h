#ifndef HOMEPAGECOLLECTIONREPLAY_H
#define HOMEPAGECOLLECTIONREPLAY_H

#include "RecipesReplay.h"
#include "src/features/Default.h"

class HomepageCollectionReplay : public RecipesReplay
{
    Q_OBJECT
public:
    explicit HomepageCollectionReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);

private:
    void receiveRecipes() override;
};

#endif // RECIPESOFHOMEPAGECOLLECTIONREPLAY_H
