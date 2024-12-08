#ifndef SEARCHRECIPESREPLY_H
#define SEARCHRECIPESREPLY_H

#include "RecipesReply.h"
#include "src/Default.h"

class SearchRecipesReply : public RecipesReply
{
    Q_OBJECT
public:
    explicit SearchRecipesReply(const QUrl &url, QNetworkAccessManager * const networkManager, int loudsNumber = Default::AttemptsNumber, QObject *parent = nullptr);
    virtual ~SearchRecipesReply() override;

private:
    void processResponse() override;
    void processError(QNetworkReply::NetworkError code) override;
    void loadRecipe(int recipeId);
    void collectResponses(RecipesReply *recipesReply, QList<Recipe*> recipe);

    bool _withSearchQuery;
    QList<Recipe*> _recipes;
    int _recipesCnt;
};

#endif // SEARCHRECIPESREPLY_H
