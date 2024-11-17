#include "Recipe.h"

Recipe::Recipe(QObject *parent)
    : QObject(parent),
      _id(-1),
      _name("Loading error"),
      _image("https://dummyimage.com/400x300/99cccc.jpg&text=Click+to+reload"),
      _categories(),
      _servingsNumber(0),
      _instructions()
{ }

Recipe::Recipe(int id, QObject *parent)
    : QObject(parent),
      _id(id),
      _name("Loading error"),
      _image("https://dummyimage.com/400x300/99cccc.jpg&text=Click+to+reload"),
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

Recipe::Recipe(const Recipe &recipe) {
    _id = recipe._id;
    _name = recipe._name;
    _image = recipe._image;
    _categories = recipe._categories;
    _servingsNumber = recipe._servingsNumber;
    _instructions = recipe._instructions;
}

Recipe& Recipe::operator=(const Recipe& recipe) {
    _id = recipe._id;
    _name = recipe._name;
    _image = recipe._image;
    _categories = recipe._categories;
    _servingsNumber = recipe._servingsNumber;
    _instructions = recipe._instructions;
    return *this;
}

int Recipe::getId() const {
    return _id;
}

const QString &Recipe::getName() const {
    return _name;
}

const QString &Recipe::getImage() const {
    return _image;
}

const QList<QString> &Recipe::getCategories() const {
    return _categories;
}

int Recipe::getServingsNumber() const {
    return _servingsNumber;
}

const QString &Recipe::getInstructionTextAt(int index) const {
    return _instructions[index].text;
}

const QList<QPair<int, int>> &Recipe::getInstructionTimersAt(int index) const {
    return _instructions[index].timers;
}

int Recipe::getInstructionsNumber() const {
    return _instructions.size();
}
