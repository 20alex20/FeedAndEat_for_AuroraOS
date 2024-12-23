#ifndef INSTRUCTIONSVIEWMODELSTATE_H
#define INSTRUCTIONSVIEWMODELSTATE_H

#include <QObject>
#include <QVariantList>

class InstructionsViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList checks READ getChecks CONSTANT)
public:
    explicit InstructionsViewModelState(QObject *parent = nullptr);
    explicit InstructionsViewModelState(int instructionsNumber, QObject *parent = nullptr);
    explicit InstructionsViewModelState(const InstructionsViewModelState *_oldState, int index, QObject *parent = nullptr);

    QVariantList getChecks() const;

    QList<bool> getChecksList() const;
    int getChecksNumber() const;

private:
    QList<bool> _checks;
};

#endif // INSTRUCTIONSVIEWMODELSTATE_H
