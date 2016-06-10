#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>

#include "Definitions.hpp"
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
    m_storageFile(nullptr),
    m_jsonDoc(nullptr)
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

    delete m_jsonDoc;
    delete m_storageFile;
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
    m_storageFile = new QSaveFile();

    bool success = m_storageFile != nullptr;
    if (success)
    {
        m_state = StorageState::Prepared;
        this->open();
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
bool JSonStorage::open()
{
    bool success = createJsonDocumentFromFile();

    if (false == checkHeader())
    {
        // If header is wrong or missing means file is corrupted, so it needs to be truncated.
        success = initFileHeader(QFile::Truncate);
    }
    else
        m_state = StorageState::Opened;

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::close()
{
    if (m_storageFile->isOpen())
    {
        QByteArray data = m_storageFile->readAll();

        QJsonObject::iterator json_magic = m_jsonDoc->object().find(JSON_KEY_HEADER_MAGIC);
        QJsonValueRef magicRef = json_magic.value();

        //        magicRef = QCryptographicHash::hash(data, QCryptographicHash::Sha3_384);
        magicRef = "Shano";

        auto var = QCryptographicHash::hash(data, QCryptographicHash::Sha3_384);
        qDebug() << "Close storage: " << var << endl;

        m_storageFile->commit();
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
bool JSonStorage::initFileHeader(auto flags)
{
    QJsonObject json_header;
    json_header[JSON_KEY_HEADER_TITLE]   = JSON_VALUE_HEADER_TITLE;
    json_header[JSON_KEY_HEADER_APP_VER] = JSON_VALUE_HEADER_APP_VER;
    json_header[JSON_KEY_HEADER_MAGIC]   = "";
    json_header[JSON_KEY_RECORDS]        = QJsonArray();

    bool success = m_storageFile->open(flags);
    if (success)
    {
        QJsonDocument doc(json_header);
        qint64 written = m_storageFile->write(doc.toJson());
        success = (written == doc.toJson().size());

        m_storageFile->commit();
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
QByteArray JSonStorage::readJsonFromFile()
{
    QByteArray dataFromFile = m_storageFile->readAll();
    // TODO: Improve reading to load in RAM only part of the file!!!

    return dataFromFile;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::checkHeader()
{
    QJsonObject::iterator json_iter;

    Q_ASSERT_X(m_jsonDoc != nullptr, __func__, "JsonDocument has not been initialized!!!");

    json_iter = m_jsonDoc->object().find(JSON_KEY_HEADER_APP_VER);
    if (json_iter == m_jsonDoc->object().end())
        return false;

    json_iter = m_jsonDoc->object().find(JSON_KEY_HEADER_TITLE);
    if (json_iter == m_jsonDoc->object().end())
        return false;

    json_iter = m_jsonDoc->object().find(JSON_KEY_HEADER_MAGIC);
    if (json_iter == m_jsonDoc->object().end())
        return false;

    json_iter = m_jsonDoc->object().find(JSON_KEY_RECORDS);
    if (json_iter == m_jsonDoc->object().end())
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::createJsonDocumentFromFile()
{

    // Choose OS specific writable application folder
    QDir storage_dir(QStandardPaths::displayName(QStandardPaths::AppLocalDataLocation));
    if (storage_dir.exists() == false)
    {
        // Create folder if it doesn't exist otherwise File cannot be created
        storage_dir.mkdir(storage_dir.absolutePath());
    }

    // Create absolute file path
    QString file_path = QString(storage_dir.absolutePath() + '/' + JSON_STORAGE_FILENAME);
    m_storageFile->setFileName(file_path);

    QFileInfo check_file(file_path);
   // check if file exists and if yes: Is it really a file and no directory?
   if (!check_file.exists())
        initFileHeader(JSON_OPEN_FILE_FLAGS);

    QByteArray data;
    bool success = m_storageFile->open(JSON_OPEN_FILE_FLAGS);
    if (success)
    {
        // Read all data from file so it can be closed
        data = readJsonFromFile();
        // Close the file immediately after data has been read
        m_storageFile->commit();
    }
    else
    {
        // TODO: report error
        success = false;
    }

    // Use the text data to form Json Document
    QJsonParseError error;
    m_jsonDoc = new QJsonDocument(QJsonDocument::fromJson(data, &error));
    qDebug() << __FILE__ << __func__ << ": Parsing Json storage file error:" << error.errorString() << endl;

    // Basic validity check
    if ((m_jsonDoc->isArray()) || (m_jsonDoc->isNull()))
    {
        // Show error
        qDebug() << "Problem loading data from storage" << endl;
    }

    qDebug() << m_jsonDoc->toJson() << endl;



    return success;
}


