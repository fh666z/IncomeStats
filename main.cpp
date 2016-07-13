#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ViewModelTransactionHandler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ViewModelTransactionHandler::getHandler()->createModels(&app);
    ViewModelTransactionHandler::getHandler()->registerTypes();

    QQmlApplicationEngine engine;

    ViewModelTransactionHandler::getHandler()->connectModelsToView(engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

