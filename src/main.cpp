#include <auroraapp.h>
#include <QtQuick>
#include "features/database/DatabaseFeature.h"
#include "features/home/HomeFeature.h"
#include "features/search/SearchFeature.h"
#include "features/instructions/InstructionsFeature.h"

int main(int argc, char *argv[]) {
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("alex_fnaf.apps"));
    application->setApplicationName(QStringLiteral("Feed & Eat"));

    DatabaseFeature databaseFeature;
    HomeFeature homeFeature(databaseFeature.getDatabaseHandler());
    SearchFeature searchFeature(databaseFeature.getDatabaseHandler());
    InstructionsFeature instructionsFeature;

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("HomeFeature", &homeFeature);
    view->rootContext()->setContextProperty("SearchFeature", &searchFeature);
    view->rootContext()->setContextProperty("InstructionsFeature", &instructionsFeature);
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/Main.qml")));
    view->show();

    return application->exec();
}
