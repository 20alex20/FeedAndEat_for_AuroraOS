#ifndef HOMEPAGECOLLECTIONREPLY_H
#define HOMEPAGECOLLECTIONREPLY_H

#include "RecipesReply.h"
#include "src/Default.h"

class HomepageCollectionReply : public RecipesReply
{
    Q_OBJECT
public:
    explicit HomepageCollectionReply(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    virtual ~HomepageCollectionReply() override;

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;
};

#endif // RECIPESOFHOMEPAGECOLLECTIONREPLY_H
