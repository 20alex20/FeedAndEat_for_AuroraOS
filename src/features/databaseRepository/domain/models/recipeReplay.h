#ifndef RECIPEREPLAY_H
#define RECIPEREPLAY_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>

class RecipeReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipeReplay(const int recipeId, QNetworkReply *recipeReplay, QNetworkAccessManager *networkManager, QObject *parent = nullptr);

signals:
    void receive(const int recipeId, QJsonObject recipe);

private:
    void getRecipe();

    int _recipeId;
    QNetworkReply *_recipeReplay;
    QNetworkAccessManager *_networkManager;
};

#endif // RECIPEREPLAY_H
