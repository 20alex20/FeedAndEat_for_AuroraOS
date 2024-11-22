#ifndef RECIPESREPLAY_H
#define RECIPESREPLAY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonObject>
#include "Recipe.h"

class RecipesReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipesReplay(QObject *parent = nullptr);
    explicit RecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent = nullptr);

signals:
    void receive(RecipesReplay *recipesReplay, QList<Recipe*> recipes);

private:
    virtual void processResponse() = 0;
    virtual void processError(QNetworkReply::NetworkError code) = 0;

protected:
    void sendResponse(QList<QJsonObject> &recipes);
    void reload();

    const QUrl _url;
    QNetworkAccessManager * const _networkManager;
    QNetworkReply *_networkReplay;
    // QTimer timer;
    int _loudsNumber;
};

#endif // RECIPESREPLAY_H
