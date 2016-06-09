#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Storage.hpp"
#include "JsonStorage.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    JSonStorage::create();
    bool exists = Storage::getStorage()->exists();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
