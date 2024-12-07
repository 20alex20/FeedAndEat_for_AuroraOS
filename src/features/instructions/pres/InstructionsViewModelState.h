#ifndef INSTRUCTIONSVIEWMODELSTATE_H
#define INSTRUCTIONSVIEWMODELSTATE_H

#include <QObject>
#include <QVariantList>
#include "src/features/database/domain/Recipe.h"

class InstructionsViewModelState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList checks READ getChecks CONSTANT)
public:
    explicit InstructionsViewModelState(QObject *parent = nullptr);
    explicit InstructionsViewModelState(int instructionsNumber, QObject *parent = nullptr);
    explicit InstructionsViewModelState(InstructionsViewModelState *_oldState, int index, QObject *parent = nullptr);

    QVariantList getChecks() const;

    int getChecksNumber() const;
    QList<bool> getChecksList() const;

private:
    QList<bool> _checks;
};

#endif // INSTRUCTIONSVIEWMODELSTATE_H
