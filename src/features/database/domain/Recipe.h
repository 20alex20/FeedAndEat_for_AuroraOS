#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QPair>

class Recipe : public QObject
{
    Q_OBJECT
public:
    struct InstructionRecord {
        const QString text;
        const QList<QPair<int, int>> timers;
    };

    explicit Recipe(QObject *parent = nullptr);
    explicit Recipe(int id, QObject *parent = nullptr);
    explicit Recipe(int id, const QString &name, const QString &image, const QList<QString> &categories,
                    int servingsNumber, const QList<InstructionRecord> &instructions, QObject *parent = nullptr);

    Q_INVOKABLE int getId() const;
    Q_INVOKABLE QString getName() const;
    Q_INVOKABLE QString getImage() const;
    Q_INVOKABLE QList<QString> getCategories() const;
    Q_INVOKABLE int getServingsNumber() const;
    Q_INVOKABLE QString getInstructionTextAt(int index) const;
    Q_INVOKABLE QList<QPair<int, int>> getInstructionTimersAt(int index) const;
    Q_INVOKABLE int getInstructionsNumber() const;

private:
    int _id;
    QString _name;
    QString _image;
    QList<QString> _categories;
    int _servingsNumber;
    QList<InstructionRecord> _instructions;
};

#endif // RECIPE_H
