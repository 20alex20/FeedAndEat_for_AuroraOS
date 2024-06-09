#include <auroraapp.h>
#include <QtQuick>
#include "features/databaseRepository/domain/repository/databaseHandler.h"
#include "features/homePage/homePageFeature.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("alex_fnaf.apps"));
    application->setApplicationName(QStringLiteral("Feed & Eat"));

    auto databaseHandler = new DatabaseHandler();
    HomePageFeature homePageFeature(databaseHandler);

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("HomePageFeature", &homePageFeature);
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/Main.qml")));
    view->show();

    return application->exec();
}
