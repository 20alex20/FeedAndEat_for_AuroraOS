#ifndef RECIPESREPLAY_H
#define RECIPESREPLAY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include "Recipe.h"

class RecipesReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipesReplay(QObject *parent = nullptr);
    explicit RecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent = nullptr);

signals:
    void receive(QList<Recipe> recipes);

private:
    virtual void processResponse() = 0;

protected:
    void sendResponse(QList<QJsonObject> recipes);
    void reload();

    const QUrl _url;
    QNetworkAccessManager * const _networkManager;
    int _loudsNumber;
    QNetworkReply *_recipesReplay;
};

#endif // RECIPESREPLAY_H
