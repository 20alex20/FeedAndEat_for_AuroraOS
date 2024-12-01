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
    Q_PROPERTY(QList<QString> categories READ getCategories CONSTANT)
    Q_PROPERTY(int servingsNumber READ getServingsNumber CONSTANT)
    Q_PROPERTY(QList<QString> instructions READ getInstructions CONSTANT)
    Q_PROPERTY(int instructionsNumber READ getInstructionsNumber CONSTANT)
public:
    explicit Recipe(QObject *parent = nullptr);
    explicit Recipe(int id, QObject *parent = nullptr);
    explicit Recipe(int id, const QString &name, const QString &image, const QList<QString> &categories, int servingsNumber,
                    const QList<QString> &instructions, const QList<QList<QPair<int, int>>> &instructionsTimers, QObject *parent = nullptr);

    int getId() const;
    bool isSuccess() const;
    QString getName() const;
    QString getImage() const;
    QList<QString> getCategories() const;
    int getServingsNumber() const;
    QList<QString> getInstructions() const;
    int getInstructionsNumber() const;

    Q_INVOKABLE QVariantList getInstructionTimers(int instructionIndex) const;

private:
    int _id;
    QString _name;
    QString _image;
    QList<QString> _categories;
    int _servingsNumber;
    QList<QString> _instructions;
    QList<QList<QPair<int, int>>> _instructionsTimers;
};

#endif // RECIPE_H
