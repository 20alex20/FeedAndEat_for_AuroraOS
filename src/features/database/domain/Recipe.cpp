#include "Recipe.h"

Recipe::Recipe(QObject *parent)
    : QObject(parent),
      _id(-1),
      _name("Loading error"),
      _image("../images/clickToReload.png"),
      _categories(),
      _servingsNumber(0),
      _instructions()
{ }

Recipe::Recipe(int id, QObject *parent)
    : QObject(parent),
      _id(id),
      _name("Loading error"),
      _image("../images/clickToReload.png"),
      _categories(),
      _servingsNumber(0),
      _instructions()
{ }

Recipe::Recipe(int id, const QString &name, const QString &image, const QList<QString> &categories,
               int servingsNumber, const QList<InstructionRecord> &instructions, QObject *parent)
    : QObject(parent),
      _id(id),
      _name(name),
      _image(image),
      _categories(categories),
      _servingsNumber(servingsNumber),
      _instructions(instructions)
{ }

int Recipe::getId() const {
    return _id;
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

QString Recipe::getInstructionTextAt(int index) const {
    return _instructions[index].text;
}

QList<QPair<int, int>> Recipe::getInstructionTimersAt(int index) const {
    return _instructions[index].timers;
}

int Recipe::getInstructionsNumber() const {
    return _instructions.size();
}
