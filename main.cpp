#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>


#include "ViewModelTransactionHandler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ViewModelTransactionHandler::getHandler()->createModels(&app);
    ViewModelTransactionHandler::getHandler()->registerTypes();
    ViewModelTransactionHandler::getHandler()->connectModelsToView(engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    ViewModelTransactionHandler::getHandler()->connectSignals(engine);

    return app.exec();
}

