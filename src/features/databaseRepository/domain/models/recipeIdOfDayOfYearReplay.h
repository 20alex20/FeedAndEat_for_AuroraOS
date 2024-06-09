#ifndef RECIPEIDOFDAYOFYEARREPLAY_H
#define RECIPEIDOFDAYOFYEARREPLAY_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class RecipeIdOfDayOfYearReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipeIdOfDayOfYearReplay(QNetworkReply *recipeIdReplay, QNetworkAccessManager *networkManager, QObject *parent = nullptr);

signals:
    void receive(const int recipeId);

private:
    void getRecipeId();

    QNetworkReply *_recipeIdReplay;
    QNetworkAccessManager *_networkManager;
};

#endif // RECIPEIDOFDAYOFYEARREPLAY_H
