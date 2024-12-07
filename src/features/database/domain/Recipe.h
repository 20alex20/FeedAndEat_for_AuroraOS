#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QVariantList>
#include <QPair>

class Recipe : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isSuccess READ isSuccess CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString image READ getImage CONSTANT)
    Q_PROPERTY(QVariantList categories READ getCategories CONSTANT)
    Q_PROPERTY(int servingsNumber READ getServingsNumber CONSTANT)
    Q_PROPERTY(QVariantList instructions READ getInstructions CONSTANT)
    Q_PROPERTY(int instructionsNumber READ getInstructionsNumber CONSTANT)
public:
    explicit Recipe(QObject *parent = nullptr);
    explicit Recipe(int id, QObject *parent = nullptr);
    explicit Recipe(int id, const QString &name, const QString &image, const QList<QString> &categories,
                    int servingsNumber, const QList<QString> &instructions, QObject *parent = nullptr);

    bool isSuccess() const;
    QString getName() const;
    QString getImage() const;
    QVariantList getCategories() const;
    int getServingsNumber() const;
    QVariantList getInstructions() const;
    int getInstructionsNumber() const;

    int getId() const;

private:
    int _id;
    QString _name;
    QString _image;
    QList<QString> _categories;
    int _servingsNumber;
    QList<QString> _instructions;
};

#endif // RECIPE_H
