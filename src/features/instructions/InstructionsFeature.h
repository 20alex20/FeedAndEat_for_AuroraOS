#ifndef INSTRUCTIONSFEATURE_H
#define INSTRUCTIONSFEATURE_H

#include "pres/InstructionsViewModel.h"

class InstructionsFeature : public QObject
{
    Q_OBJECT
public:
    explicit InstructionsFeature(QObject *parent = nullptr);

    Q_INVOKABLE InstructionsViewModel *getInstructionsViewModel(QObject *parent = nullptr);
};

#endif // INSTRUCTIONSFEATURE_H
