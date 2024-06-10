TARGET = alex_fnaf.apps.FeedAndEat

QT += network

CONFIG += auroraapp

SOURCES += \
    src/features/databaseRepository/domain/models/recipeIdsReplay.cpp \
    src/features/databaseRepository/domain/models/recipesOfHomepageCollectionReplay.cpp \
    src/features/databaseRepository/domain/repository/databaseHandler.cpp \
    src/features/databaseRepository/domain/models/recipeIdOfDayOfYearReplay.cpp \
    src/features/databaseRepository/domain/models/recipeReplay.cpp \
    src/features/homePage/homePageFeature.cpp \
    src/features/homePage/pres/homePageViewModel.cpp \
    src/main.cpp

HEADERS += \
    src/features/databaseRepository/domain/models/recipeIdsReplay.h \
    src/features/databaseRepository/domain/models/recipesOfHomepageCollectionReplay.h \
    src/features/databaseRepository/domain/repository/databaseHandler.h \
    src/features/databaseRepository/domain/models/recipeIdOfDayOfYearReplay.h \
    src/features/databaseRepository/domain/models/recipeReplay.h \
    src/features/homePage/homePageFeature.h \
    src/features/homePage/pres/homePageViewModel.h

DISTFILES += rpm/alex_fnaf.apps.FeedAndEat.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/alex_fnaf.apps.FeedAndEat.ts \
    translations/alex_fnaf.apps.FeedAndEat-ru.ts
