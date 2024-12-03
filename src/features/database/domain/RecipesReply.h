#ifndef RECIPESREPLY_H
#define RECIPESREPLY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include "Recipe.h"

class RecipesReply : public QObject
{
    Q_OBJECT
public:
    explicit RecipesReply(QObject *parent = nullptr);
    explicit RecipesReply(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent = nullptr);
    virtual ~RecipesReply();

    QString getUrl();

signals:
    void receive(RecipesReply *recipesReply, QList<Recipe*> recipes);

private:
    virtual void processResponse() = 0;
    virtual void processError(QNetworkReply::NetworkError code) = 0;

protected:
    void sendResponse(QList<QJsonObject> &recipes);
    void reload();

    const QUrl _url;
    QNetworkAccessManager * const _networkManager;
    QNetworkReply *_networkReply;
    int _loudsNumber;
};

#endif // RECIPESREPLY_H
