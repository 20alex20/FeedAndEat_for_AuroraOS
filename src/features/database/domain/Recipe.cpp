#include "Recipe.h"

Recipe::Recipe(QObject *parent)
    : QObject(parent),
      _id(-1),
      _name("Loading error"),
      _image("../images/clickToReload.png"),
      _categories(),
      _servingsNumber(0),
      _instructions(),
      _instructionsTimers()
{ }

Recipe::Recipe(int id, QObject *parent)
    : QObject(parent),
      _id(id),
      _name("Loading error"),
      _image("../images/clickToReload.png"),
      _categories(),
      _servingsNumber(0),
      _instructions(),
      _instructionsTimers()
{ }

Recipe::Recipe(int id, const QString &name, const QString &image, const QList<QString> &categories, int servingsNumber,
               const QList<QString> &instructions, const QList<QList<QPair<int, int>>> &instructionsTimers, QObject *parent)
    : QObject(parent),
      _id(id),
      _name(name),
      _image(image),
      _categories(categories),
      _servingsNumber(servingsNumber),
      _instructions(instructions),
      _instructionsTimers(instructionsTimers)
{ }

int Recipe::getId() const {
    return _id;
}

bool Recipe::isSuccess() const {
    return !_instructions.isEmpty();
}

QString Recipe::getName() const {
    return _name;
}

QString Recipe::getImage() const {
    return _image;
}

QList<QString> Recipe::getCategories() const {
    return _categories;
}

int Recipe::getServingsNumber() const {
    return _servingsNumber;
}

QList<QString> Recipe::getInstructions() const {
    return _instructions;
}

int Recipe::getInstructionsNumber() const {
    return _instructions.size();
}

QVariantList Recipe::getInstructionTimers(int index) const {
    QVariantList instructionTimers;
    if (index >= 0 && index < _instructionsTimers.size())
        for (auto &instructionTimer: _instructionsTimers[index])
            instructionTimers.append(QVariant::fromValue<QPair<int, int>>(instructionTimer));
    return instructionTimers;
}
