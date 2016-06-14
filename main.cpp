#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Storage.hpp"
#include "JsonStorage.hpp"
#include "IncomeOrder.hpp"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    JSonStorage::create();
    bool exists = Storage::getStorage()->exists();
    if (exists)
    {
        if (Storage::getState() == StorageState::Opened)
        {
            Storage::getStorage()->writeRecord(1000.0, QDate::currentDate().toString(), "Salary", "test");

            IncomeOrder *rec = Storage::getStorage()->readRecordByID(11);
            if (rec)
                qDebug() << "ID: " << rec->id() << " : " << rec->amount() << " : " << rec->typeString() << endl;
            Storage::getStorage()->close();
        }
    }



    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
