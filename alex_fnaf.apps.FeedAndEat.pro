TARGET = alex_fnaf.apps.FeedAndEat

QT += network

CONFIG += auroraapp

SOURCES += \
    src/features/database/DatabaseFeature.cpp \
    src/features/database/domain/DailyRecipeReplay.cpp \
    src/features/database/domain/HomepageCollectionReplay.cpp \
    src/features/database/domain/Recipe.cpp \
    src/features/database/domain/RecipeReplay.cpp \
    src/features/database/domain/RecipesReplay.cpp \
    src/features/database/domain/SearchRecipesReplay.cpp \
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
    src/features/database/domain/DailyRecipeReplay.h \
    src/features/database/domain/HomepageCollectionReplay.h \
    src/features/database/domain/Recipe.h \
    src/features/database/domain/RecipeReplay.h \
    src/features/database/domain/RecipesReplay.h \
    src/features/database/domain/SearchRecipesReplay.h \
    src/features/database/data/DatabaseHandler.h \
    src/features/home/HomeFeature.h \
    src/features/home/pres/HomeViewModel.h \
    src/features/home/pres/HomeViewModelState.h \
    src/features/search/SearchFeature.h \
    src/features/search/pres/SearchViewModel.h \
    src/features/search/pres/SearchViewModelState.h

DISTFILES += rpm/alex_fnaf.apps.FeedAndEat.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/alex_fnaf.apps.FeedAndEat.ts \
    translations/alex_fnaf.apps.FeedAndEat-ru.ts
