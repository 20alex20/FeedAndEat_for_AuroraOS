#ifndef RECIPEIDSREPLAY_H
#define RECIPEIDSREPLAY_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QList>

class RecipeIdsReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipeIdsReplay(QNetworkReply *recipeIdsReplay, QNetworkAccessManager *networkManager, QObject *parent = nullptr);

signals:
    void receive(QList<int> recipeIds);

private:
    void getRecipeIds();

    QNetworkReply *_recipeIdsReplay;
    QNetworkAccessManager *_networkManager;
};

#endif // RECIPEIDSREPLAY_H
