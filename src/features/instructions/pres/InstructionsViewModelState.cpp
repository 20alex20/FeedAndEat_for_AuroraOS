#include "InstructionsViewModelState.h"

InstructionsViewModelState::InstructionsViewModelState(QObject *parent)
    : QObject(parent),
      _checks()
{ }

InstructionsViewModelState::InstructionsViewModelState(int instructionsNumber, QObject *parent)
    : QObject(parent)
{
    _checks.reserve(instructionsNumber);
    for (int i = 0; i < instructionsNumber; i++)
        _checks.append(false);
}

InstructionsViewModelState::InstructionsViewModelState(InstructionsViewModelState *_oldState, int index, QObject *parent)
    : QObject(parent),
      _checks(_oldState->getChecksList())
{
    if (index >= 0 && index < _checks.size())
        _checks[index] = !_checks[index];
}

QVariantList InstructionsViewModelState::getChecks() const {
    QVariantList checks;
    checks.reserve(_checks.size());
    for (auto check: _checks)
        checks.append(QVariant::fromValue<bool>(check));
    return checks;
}

int InstructionsViewModelState::getChecksNumber() const {
    return _checks.size();
}

QList<bool> InstructionsViewModelState::getChecksList() const {
    return _checks;
}
