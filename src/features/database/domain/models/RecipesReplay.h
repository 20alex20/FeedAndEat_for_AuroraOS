#ifndef RECIPESREPLAY_H
#define RECIPESREPLAY_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

class RecipesReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipesReplay(const QUrl &url, QNetworkAccessManager * const networkManager, const int loudsNumber, QObject *parent)
        : QObject(parent),
          _url(url),
          _networkManager(networkManager),
          _loudsNumber(loudsNumber),
          _recipesReplay(_networkManager->get(QNetworkRequest(url)))
    {
        connect(_recipesReplay, &QNetworkReply::readyRead, this, &RecipesReplay::receiveRecipes);
    }

signals:
    void receive(QList<QJsonObject> recipes);

private:
    virtual void receiveRecipes() = 0;

protected:
    void reload() {
        _recipesReplay = _networkManager->get(QNetworkRequest(_url));
        connect(_recipesReplay, &QNetworkReply::readyRead, this, &RecipesReplay::receiveRecipes);
    }

    const QUrl _url;
    QNetworkAccessManager * const _networkManager;
    int _loudsNumber;
    QNetworkReply *_recipesReplay;
};

#endif // RECIPESREPLAY_H
