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
    qmlRegisterType<SearchViewModel>("FeedAndEat.Feature.Search", 1, 0, "SearchViewModel");
    qmlRegisterType<SearchViewModelState>("FeedAndEat.Feature.Search", 1, 0, "SearchViewModelState");
    qRegisterMetaType<SearchViewModelState::Status>("SearchViewModelState::Status");
}

SearchViewModel *SearchFeature::getSearchViewModel(QObject *parent) {
    return new SearchViewModel(_databaseHandler, parent);
}
