#include <QDir>
#include <QFile>
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
    m_storageFile(nullptr)
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
void JSonStorage::writeRecord(IncomeOrder *new_order)
{
    m_incomeRecords->push_back(new_order);
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::writeRecord(int id, double amount, QString date, QString type, QString comment)
{
    m_incomeRecords->push_back(new IncomeOrder(id, amount, date, type, comment));
}


//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
IncomeOrder& JSonStorage::readRecordByID(unsigned id) const
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::readAllRecords(std::vector<IncomeOrder *> &recordsList) const
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::prepareStorage()
{
    m_storageFile = new QFile();

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

    // Extract the data from the file
    bool success = m_storageFile->open(JSON_OPEN_FILE_FLAGS);
    if (false == success)
        return false;

    QByteArray dataFromFile = m_storageFile->readAll();
    m_storageFile->close();

    // Use the text data to form Json Document
    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(dataFromFile, &error));
    if (false == verifyCreatedJson(doc, error))
    {
        QJsonObject headerObj;
        initHeader(headerObj);
        doc.setObject(headerObj);
    }

    // Only if data is valid proceed to extracting income records
    extractAllRecords(doc);

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
    QJsonDocument doc;
    serializeRecordsToJson(doc);

    m_storageFile->open(QFile::ReadWrite | QFile::Truncate | QFile::Text);
    m_storageFile->write(doc.toJson());
    m_storageFile->close();

    m_state = StorageState::Closed;

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
void JSonStorage::serializeRecordsToJson(QJsonDocument &doc)
{
    QJsonObject rootObject;

    initHeader(rootObject);

    QJsonArray recordsArray;
    foreach (const IncomeOrder &rec, *m_incomeRecords)
    {
        QJsonObject jsonRecord;
        jsonRecord[INCOME_ORDER_ID_KEY]     = rec.id();
        jsonRecord[INCOME_ORDER_AMOUNT_KEY] = rec.amount();
        jsonRecord[INCOME_ORDER_DATE_KEY]   = rec.dateString();
        jsonRecord[INCOME_ORDER_TYPE_KEY]   = rec.typeString();
        jsonRecord[INCOME_ORDER_COMMENT_KEY]= rec.comment();

        recordsArray.append(jsonRecord);
    }
    rootObject[JSON_KEY_RECORDS] = recordsArray;
    doc.setObject(rootObject);

    rootObject[JSON_KEY_HEADER_MAGIC] = QString(QCryptographicHash::hash(doc.toJson(), QCryptographicHash::Sha3_384));
    doc.setObject(rootObject);
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::extractAllRecords(const QJsonDocument &doc)
{
    m_incomeRecords = new std::vector<IncomeOrder*>();
    QJsonArray entries = doc.object()[JSON_KEY_RECORDS].toArray();

    foreach (const QJsonValue &jsonValue, entries)
    {
        QJsonObject record = jsonValue.toObject();
        IncomeOrder* current_order = new IncomeOrder(
                    record.value(INCOME_ORDER_ID_KEY).toInt(),
                    record.value(INCOME_ORDER_AMOUNT_KEY).toDouble(),
                    record.value(INCOME_ORDER_DATE_KEY).toString(),
                    record.value(INCOME_ORDER_TYPE_KEY).toString(),
                    record.value(INCOME_ORDER_COMMENT_KEY).toString()
                    );

        m_incomeRecords->push_back(current_order);
    }
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void JSonStorage::initHeader(QJsonObject &headerObj)
{
    headerObj[JSON_KEY_HEADER_TITLE]   = JSON_VALUE_HEADER_TITLE;
    headerObj[JSON_KEY_HEADER_APP_VER] = JSON_VALUE_HEADER_APP_VER;
    headerObj[JSON_KEY_HEADER_MAGIC]   = "";
    headerObj[JSON_KEY_RECORDS]        = QJsonArray();
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::checkHeader(const QJsonDocument &doc)
{
    QJsonObject::iterator json_iter;

    json_iter = doc.object().find(JSON_KEY_HEADER_APP_VER);
    if (json_iter == doc.object().end())
        return false;

    json_iter = doc.object().find(JSON_KEY_HEADER_TITLE);
    if (json_iter == doc.object().end())
        return false;

    json_iter = doc.object().find(JSON_KEY_HEADER_MAGIC);
    if (json_iter == doc.object().end())
        return false;

    json_iter =doc.object().find(JSON_KEY_RECORDS);
    if (json_iter == doc.object().end())
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool JSonStorage::verifyCreatedJson(const QJsonDocument &doc, QJsonParseError &error)
{

    if (error.errorString() != "no error occurred")
        qDebug() << __FILE__ << __func__ << ": Parsing Json storage file error:" << error.errorString() << endl;

    // Basic validity check
    if ((doc.isArray()) || (doc.isNull()) || (false == checkHeader(doc)))
    {
        // Show error
        qDebug() << "Problem loading data from storage" << endl;
        qDebug() << doc.toJson() << endl;

        return false;
    }

    return true;
}


