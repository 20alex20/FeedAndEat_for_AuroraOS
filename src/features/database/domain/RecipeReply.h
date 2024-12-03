#ifndef RECIPEREPLY_H
#define RECIPEREPLY_H

#include "RecipesReply.h"
#include "src/Default.h"

class RecipeReply : public RecipesReply
{
    Q_OBJECT
public:
    explicit RecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, const int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    explicit RecipeReply(const QUrl &url, QNetworkAccessManager * const networkManager, int recipeId, QObject *parent);
    virtual ~RecipeReply() override;

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;

    int _recipeId;
};

#endif // RECIPEREPLY_H
