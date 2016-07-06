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
    IncomeOrderModel *dataModel = nullptr;
    JSonStorage::create();
#endif
#ifdef USE_SQL_STORAGE
    IncomeOrderSQLModel *dataModel = nullptr;
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
    dataModel = new IncomeOrderSQLModel(&app, (QSqlDatabase *)(Storage::getStorage()->getConnection()));
    dataModel->setTable("records");
    dataModel->select();
#endif
    }

    IncomeTypeModel *typeModel = new IncomeTypeModel();
    IncomeOrder new_order;


    QQmlApplicationEngine engine;
    QQmlContext *ctx = engine.rootContext();

    ctx->setContextProperty("new_order", &new_order);
    ctx->setContextProperty("incomeOrderModel", dataModel);
    ctx->setContextProperty("incomeTypeModel", typeModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

