#include "InstructionsFeature.h"
#include <QtQml>

InstructionsFeature::InstructionsFeature(QObject *parent)
    : QObject(parent)
{
    qmlRegisterType<InstructionsViewModel>("FeedAndEat.Feature.Instructions", 1, 0, "InstructionsViewModel");
    qmlRegisterType<InstructionsViewModelState>("FeedAndEat.Feature.Instructions", 1, 0, "InstructionsViewModelState");
}

InstructionsViewModel *InstructionsFeature::getInstructionsViewModel(QObject *parent) {
    return new InstructionsViewModel(parent);
}
