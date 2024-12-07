#ifndef INSTRUCTIONSVIEWMODEL_H
#define INSTRUCTIONSVIEWMODEL_H

#include <QObject>
#include "InstructionsViewModelState.h"

class InstructionsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InstructionsViewModelState *state READ getState NOTIFY stateChanged)
public:
    explicit InstructionsViewModel(QObject *parent = nullptr);
    ~InstructionsViewModel();

    Q_INVOKABLE void bind(int instructionsNumber);
    Q_INVOKABLE void changeCheck(int index);

    void setState(InstructionsViewModelState* newState);
    InstructionsViewModelState *getState() const;
signals:
    void stateChanged();

private:

    InstructionsViewModelState *_state;
};

#endif // INSTRUCTIONSVIEWMODEL_H
