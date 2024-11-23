#include "SearchFeature.h"
#include <QtQml>

SearchFeature::SearchFeature(QObject *parent)
    : QObject(parent),
      _databaseHandler(nullptr)
{ }

SearchFeature::SearchFeature(DatabaseHandler * const databaseHandler, QObject *parent)
    : QObject(parent),
      _databaseHandler(databaseHandler)
{
    qmlRegisterType<SearchViewModel>("FeadAndEat.Feature.Search", 1, 0, "SearchViewModel");
    qmlRegisterType<SearchViewModelState>("FeadAndEat.Feature.Search", 1, 0, "SearchViewModelState");
}

SearchViewModel *SearchFeature::getSearchViewModel(QObject *parent) {
    return new SearchViewModel(_databaseHandler, parent);
}
