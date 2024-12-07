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
               int servingsNumber, const QList<QString> &instructions, QObject *parent)
    : QObject(parent),
      _id(id),
      _name(name),
      _image(image),
      _categories(categories),
      _servingsNumber(servingsNumber),
      _instructions(instructions)
{ }

bool Recipe::isSuccess() const {
    return !_instructions.isEmpty();
}

QString Recipe::getName() const {
    return _name;
}

QString Recipe::getImage() const {
    return _image;
}

QVariantList Recipe::getCategories() const {
    QVariantList categories;
    categories.reserve(_categories.size());
    for (auto &category: _categories)
        categories.append(QVariant::fromValue<QString>(category));
    return categories;
}

int Recipe::getServingsNumber() const {
    return _servingsNumber;
}

QVariantList Recipe::getInstructions() const {
    QVariantList instructions;
    instructions.reserve(_instructions.size());
    for (auto &recipe: _instructions)
        instructions.append(QVariant::fromValue<QString>(recipe));
    return instructions;
}

int Recipe::getInstructionsNumber() const {
    return _instructions.size();
}

int Recipe::getId() const {
    return _id;
}
