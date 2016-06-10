#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Storage.hpp"
#include "JsonStorage.hpp"
#include "IncomeOrder.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    JSonStorage::create();
    bool exists = Storage::getStorage()->exists();
    if (exists)
    {
        if (Storage::getState() == StorageState::Opened)
        {
            IncomeOrder new_income(1000, "10-05-2015", IncomeOrder::IncomeType::Salary, "test");
            Storage::getStorage()->writeRecord(new_income);
            Storage::getStorage()->close();
        }
    }



    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
