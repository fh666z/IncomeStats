#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ViewModelTransactionHandler.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ViewModelTransactionHandler viewManager(&app, &engine);
    viewManager.createModels(&app);
    viewManager.registerTypes();
    viewManager.connectModelsToView();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    viewManager.connectSignals();

    return app.exec();
}

