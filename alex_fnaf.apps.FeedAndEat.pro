TARGET = alex_fnaf.apps.FeedAndEat

QT += network

CONFIG += auroraapp

SOURCES += \
    src/features/database/DatabaseFeature.cpp \
    src/features/database/domain/models/DailyRecipeReplay.cpp \
    src/features/database/domain/models/HomepageCollectionReplay.cpp \
    src/features/database/domain/models/RecipeReplay.cpp \
    src/features/database/domain/models/SearchRecipesReplay.cpp \
    src/features/database/domain/repository/DatabaseHandler.cpp \
    src/features/home/homeFeature.cpp \
    src/features/home/pres/homeViewModel.cpp \
    src/main.cpp

HEADERS += \
    src/features/Default.h \
    src/features/database/DatabaseFeature.h \
    src/features/database/domain/models/DailyRecipeReplay.h \
    src/features/database/domain/models/HomepageCollectionReplay.h \
    src/features/database/domain/models/RecipeReplay.h \
    src/features/database/domain/models/RecipesReplay.h \
    src/features/database/domain/models/SearchRecipesReplay.h \
    src/features/database/domain/repository/DatabaseHandler.h \
    src/features/home/homeFeature.h \
    src/features/home/pres/homeViewModel.h

DISTFILES += rpm/alex_fnaf.apps.FeedAndEat.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/alex_fnaf.apps.FeedAndEat.ts \
    translations/alex_fnaf.apps.FeedAndEat-ru.ts
