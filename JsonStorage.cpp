#include <QDir>
#include <QFile>
#include <qiodevice.h>
#include <QStandardPaths>
#include <QDebug>

#include "JsonStorage.hpp"


void JSonStorage::create()
{
    if (m_pDataStorage == nullptr)
    {
        m_pDataStorage = new JSonStorage();
        m_pDataStorage->initialize("storage.json");
    }
    else
        qDebug() << "Storage has already been created!!!" << endl;
}

bool JSonStorage::writeRecord(IncomeOrder &new_order)
{
    Q_UNUSED(new_order)
    return true;
}

IncomeOrder& JSonStorage::readRecord()
{

}

JSonStorage::JSonStorage() {}

JSonStorage::~JSonStorage() {}

bool JSonStorage::initialize(QString file_name)
{
    QDir storage_dir(QStandardPaths::displayName(QStandardPaths::AppDataLocation));
    QString file_path = QString(storage_dir.absolutePath() + '/' + file_name);
    QFile *storage_file = new QFile(file_path);

    return storage_file->open(QFile::ReadWrite);
}

bool JSonStorage::open()
{
    return true;
}

bool JSonStorage::close()
{
    return true;
}
