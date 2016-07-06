#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>
#include <QQmlContext>
#include <QQmlEngine>

#include <vector>

#include "Storage.hpp"
#include "JsonStorage.hpp"
#include "SQLStorage.hpp"
#include "IncomeOrder.hpp"
#include "IncomeOrderModel.hpp"
#include "IncomeOrderSQLModel.hpp"
#include "Definitions.hpp"

#include <QDebug>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterUncreatableType<IncomeType>("CPPEnums", 1, 0, "IncomeType", "Export enums from C++");


#ifdef USE_JSON_STORAGE
    IncomeOrderModel *model = nullptr;
    JSonStorage::create();
#endif
#ifdef USE_SQL_STORAGE
    IncomeOrderSQLModel *model = nullptr;
    SQLStorage::create();
#endif
    qDebug() << QSqlDatabase::drivers() << endl;
    bool exists = Storage::getStorage()->exists();


    if (exists)
    {
 #ifdef USE_JSON_STORAGE
        // TODO: Think of lazy loading
        for (int index = 0; index < Storage::getStorage()->getRecordsCount(); index++)
            model->addIncomeOrder(*Storage::getStorage()->readRecordByID(index));
#endif
#ifdef USE_SQL_STORAGE
    model = new IncomeOrderSQLModel(&app, (QSqlDatabase *)(Storage::getStorage()->getConnection()));
    model->setTable("records");
    model->select();
#endif
    }


    QQmlApplicationEngine engine;
    QQmlContext *ctx = engine.rootContext();

    ctx->setContextProperty("incomeOrderModel", model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

