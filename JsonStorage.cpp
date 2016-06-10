#include <QDir>
#include <QFile>
#include <qiodevice.h>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "JsonStorage.hpp"
#include "IncomeOrder.hpp"


//==================================================================================================
// Constructors/Descrutctor
//==================================================================================================
//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
JSonStorage::JSonStorage() :
    m_storage_file(nullptr),
    m_json_doc(nullptr)
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
JSonStorage::~JSonStorage()
{
    close();
}


//==================================================================================================
// Public methods
//==================================================================================================
//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::create()
{
    if (m_pDataStorage == nullptr)
    {
        m_pDataStorage = new JSonStorage();
        m_pDataStorage->prepareStorage();
    }
    else
        qDebug() << "Storage has already been created!!!" << endl;
}


//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::writeRecord(IncomeOrder &new_order)
{
    QJsonObject record;
    record["amount"] = new_order.amount();
    record["date"] = new_order.dateString();
    record["type"] = new_order.typeString();
    record["comment"] = new_order.comment();

    return true;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
IncomeOrder& JSonStorage::readRecord()
{

}


//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::prepareStorage()
{
    m_storage_file = new QFile();

    bool success = m_storage_file != nullptr;
    if (success)
    {
        m_state = StorageState::Prepared;
        this->open("storage.json");
    }
    else
    {
        // TODO: report error
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::open(QString file_name)
{
    QDir storage_dir(QStandardPaths::displayName(QStandardPaths::AppLocalDataLocation));
    if (storage_dir.exists() == false)
    {
        storage_dir.mkdir(storage_dir.absolutePath());
    }
    QString file_path = QString(storage_dir.absolutePath() + '/' + file_name);

    m_storage_file->setFileName(file_path);
    bool success = m_storage_file->open(QFile::ReadWrite | QFile::Text);
    if (success)
    {
        // File is empty, so JSon must be initialized with header
        if (m_storage_file->size() == 0)
        {
            success = initFileHeader();
        }

        createJsonDocument();

        m_state = StorageState::Opened;
    }
    else
    {
        // TODO: report error
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::close()
{
    if (m_storage_file->isOpen())
    {
        m_storage_file->close();
        m_state = StorageState::Closed;
    }

    return true;
}

//==================================================================================================
// Private methods
//==================================================================================================
//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::initFileHeader()
{
    QJsonObject json_header;
    json_header["title"]        = "IncomStats JSon storage file";
    json_header["appVersion"]   = "1.0";
    json_header["records"]      = QJsonArray();
    QJsonDocument doc(json_header);

    qint64 written = m_storage_file->write(doc.toJson());
    bool success = (written == doc.toJson().size());
    if (success)
        m_storage_file->flush();

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::createJsonDocument()
{
    m_json_doc = new QJsonDocument(QJsonDocument::fromJson(m_storage_file->readAll()));
    QJsonArray parse_obj;

    qDebug() << m_json_doc->isArray() << endl;
//    parse_obj = m_json_doc->array();


//    qDebug() << parse_obj[0].toString() << endl;
}



