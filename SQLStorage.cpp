#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "SQLStorage.hpp"
#include "Definitions.hpp"


//==================================================================================================
// Constructors/Descrutctor
//==================================================================================================
//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
SQLStorage::SQLStorage()
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
SQLStorage::~SQLStorage()
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
void SQLStorage::create()
{
    if (m_pDataStorage == nullptr)
    {
        m_pDataStorage = new SQLStorage();
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
bool SQLStorage::prepareStorage()
{
    // TODO: CHANGE Here
    m_dbConnDefault = new QSqlDatabase();
    m_dbConnDefault->addDatabase(QSQL_DB_TYPE);
    m_dbConnDefault->setHostName(QSQL_HOSTNAME);
    m_dbConnDefault->setDatabaseName(QSQL_DB_NAME);
    m_dbConnDefault->setUserName(QSQL_USER);
    m_dbConnDefault->setPassword(QSQL_USER_PASS);

    m_state = StorageState::Prepared;
    this->open();

    return true;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool SQLStorage::open()
{
    bool success = m_dbConnDefault->open();

    qDebug() << m_dbConnDefault->lastError().text() << endl;

    if (success)
        m_state = StorageState::Opened;

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool SQLStorage::close()
{
//    QJsonDocument doc;
//    serializeRecordsToJson(doc);

//    m_storageFile->open(QFile::ReadWrite | QFile::Truncate | QFile::Text);
//    m_storageFile->write(doc.toJson());
//    m_storageFile->close();

    m_state = StorageState::Closed;

    return true;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void SQLStorage::writeRecord(IncomeOrder *new_order)
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void SQLStorage::writeRecord(double amount, QString date, QString type, QString comment)
{

}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
IncomeOrder *SQLStorage::readRecordByID(int id) const
{
    return nullptr;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
std::vector<IncomeOrder *> *SQLStorage::readAllRecords() const
{
    return nullptr;
}
