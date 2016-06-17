#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

#include <vector>

#include "Storage.hpp"
#include "JsonStorage.hpp"
#include "IncomeOrder.hpp"
#include "IncomeOrderModel.hpp"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    IncomeOrderModel model;

    JSonStorage::create();
    bool exists = Storage::getStorage()->exists();
    if (exists)
    {
        // TODO: Think of lazy loading
        for (int index = 0; index < Storage::getStorage()->getRecordsCount(); index++)
            model.addIncomeOrder(*Storage::getStorage()->readRecordByID(index));
    }

    QQmlApplicationEngine engine;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("incomeOrderModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
