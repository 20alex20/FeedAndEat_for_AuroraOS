#include "InstructionsViewModel.h"

InstructionsViewModel::InstructionsViewModel(QObject *parent)
    : QObject(parent),
      _state(new InstructionsViewModelState())
{ }

InstructionsViewModel::~InstructionsViewModel() {
    _state->deleteLater();
}

void InstructionsViewModel::bind(int instructionsNumber) {
    setState(new InstructionsViewModelState(instructionsNumber));
}

void InstructionsViewModel::changeCheck(int index) {
    if (index >= 0 && index < _state->getChecksNumber())
        setState(new InstructionsViewModelState(_state, index));
}

InstructionsViewModelState *InstructionsViewModel::getState() const {
    return _state;
}

void InstructionsViewModel::setState(InstructionsViewModelState *newState) {
    auto oldState = _state;
    _state = newState;
    emit stateChanged();
    oldState->deleteLater();
}
