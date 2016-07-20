#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>


#include "ViewManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ViewManager::getHandler()->createModels(&app);
    ViewManager::getHandler()->registerTypes();
    ViewManager::getHandler()->connectModelsToView(engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    ViewManager::getHandler()->connectSignals(engine);
    //ViewManager::getHandler()->createViewMapping(engine);

    return app.exec();
}

