#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

#include <vector>

#include "Storage.hpp"
#include "JsonStorage.hpp"
#include "SQLStorage.hpp"
#include "IncomeOrder.hpp"
#include "IncomeOrderModel.hpp"
#include "Definitions.hpp"

#include <QDebug>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    IncomeOrderModel model;

#ifdef USE_JSON_STORAGE
    JSonStorage::create();
#endif
#ifdef USE_SQL_STORAGE
    SQLStorage::create();
#endif
    qDebug() << QSqlDatabase::drivers() << endl;
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
