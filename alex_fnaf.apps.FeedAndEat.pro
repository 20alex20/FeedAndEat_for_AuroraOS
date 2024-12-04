TARGET = alex_fnaf.apps.FeedAndEat

QT += network

CONFIG += auroraapp

SOURCES += \
    src/features/database/DatabaseFeature.cpp \
    src/features/database/domain/DailyRecipeReply.cpp \
    src/features/database/domain/HomepageCollectionReply.cpp \
    src/features/database/domain/Recipe.cpp \
    src/features/database/domain/RecipeReply.cpp \
    src/features/database/domain/RecipesReply.cpp \
    src/features/database/domain/SearchRecipesReply.cpp \
    src/features/database/data/DatabaseHandler.cpp \
    src/features/home/HomeFeature.cpp \
    src/features/home/pres/HomeViewModel.cpp \
    src/features/home/pres/HomeViewModelState.cpp \
    src/features/search/SearchFeature.cpp \
    src/features/search/pres/SearchViewModel.cpp \
    src/features/search/pres/SearchViewModelState.cpp \
    src/main.cpp

HEADERS += \
    src/Default.h \
    src/features/database/DatabaseFeature.h \
    src/features/database/domain/DailyRecipeReply.h \
    src/features/database/domain/HomepageCollectionReply.h \
    src/features/database/domain/Recipe.h \
    src/features/database/domain/RecipeReply.h \
    src/features/database/domain/RecipesReply.h \
    src/features/database/domain/SearchRecipesReply.h \
    src/features/database/data/DatabaseHandler.h \
    src/features/home/HomeFeature.h \
    src/features/home/pres/HomeViewModel.h \
    src/features/home/pres/HomeViewModelState.h \
    src/features/search/SearchFeature.h \
    src/features/search/pres/SearchViewModel.h \
    src/features/search/pres/SearchViewModelState.h

DISTFILES += rpm/alex_fnaf.apps.FeedAndEat.spec \
    qml/cover/CoverPage.qml \
    qml/dataObjects/RecipeCardHeight.qml \
    qml/dataObjects/CategoriesList.qml \
    qml/items/RecipeCard.qml \
    qml/items/DailyRecipe.qml \
    qml/items/RecipesCollection.qml \
    qml/items/SearchButtonCard.qml \
    qml/items/SearchCategoryCard.qml \
    qml/pages/HomePage.qml \
    qml/pages/InstructionsPage.qml \
    qml/pages/RecipePage.qml \
    qml/pages/SearchPage.qml \
    qml/Main.qml

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/alex_fnaf.apps.FeedAndEat.ts \
    translations/alex_fnaf.apps.FeedAndEat-ru.ts
