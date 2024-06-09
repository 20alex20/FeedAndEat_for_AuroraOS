#ifndef RECIPESOFHOMEPAGECOLLECTIONREPLAY_H
#define RECIPESOFHOMEPAGECOLLECTIONREPLAY_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QList>

class RecipesOfHomepageCollectionReplay : public QObject
{
    Q_OBJECT
public:
    explicit RecipesOfHomepageCollectionReplay(QString &collectionName, QNetworkReply *recipesReplay, QNetworkAccessManager *networkManager, QObject *parent = nullptr);

signals:
    void receive(QString &collectionName, QList<QJsonObject> recipes);

private:
    void getRecipes();

    QString _collectionName;
    QNetworkReply *_recipesReplay;
    QNetworkAccessManager *_networkManager;
};

#endif // RECIPESOFHOMEPAGECOLLECTIONREPLAY_H
