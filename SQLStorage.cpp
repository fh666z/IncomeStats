#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
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
    m_dbConnDefault = new QSqlDatabase(QSqlDatabase::addDatabase(QSQL_DB_TYPE));

    m_dbConnDefault->setHostName(QSQL_HOSTNAME);
    m_dbConnDefault->setPort(QSQL_HOST_PORT);
    m_dbConnDefault->setDatabaseName(QSQL_DB_NAME);
    m_dbConnDefault->setUserName(QSQL_USER);
    m_dbConnDefault->setPassword(QSQL_USER_PASS);

    if (m_dbConnDefault->isValid() == false)
        qDebug() << "Invalid Database!" << endl;

    m_state = StorageState::Prepared;

    return open();
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool SQLStorage::open()
{
    bool success = m_dbConnDefault->open();

    if (success)
    {
        qDebug() << "Connection to:" << m_dbConnDefault->hostName() << ":" << m_dbConnDefault->port() << endl << "Driver:" << m_dbConnDefault->driver()  << "successfull." << endl;
        m_state = StorageState::Opened;

        QSqlQuery createTable(*m_dbConnDefault);
        success = createTable.prepare("create table if not exists "
                             "records(id integer unique not null auto_increment, "
                             "date DATE, "
                             "amount DOUBLE, "
                             "type ENUM('Salary','Bonus','Other'), "
                             "comment VARCHAR(100),"
                             "PRIMARY KEY(id))");
        // Prepare succeeded
        if (success)
            success = createTable.exec();
        else
            qDebug() << "Prepare SQL query failed:" << m_dbConnDefault->lastError().text() << endl;

        // Exec succeeded
        if (success == false)
            qDebug() << "Create table 'records' failed:" << m_dbConnDefault->lastError().text() << endl;


    }
    else
        qDebug() << "Connection failed:"<< m_dbConnDefault->hostName() << ":" << m_dbConnDefault->port() << endl << "Driver:" << m_dbConnDefault->driver() << "Error:"<< m_dbConnDefault->lastError().text() << endl;

    return success;
}

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
bool SQLStorage::close()
{
    m_dbConnDefault->close();

    delete m_dbConnDefault;
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

//--------------------------------------------------------------------------------------------------
// Purpose:
// Input:
// Output:
//--------------------------------------------------------------------------------------------------
void* SQLStorage::getConnection()
{
    return m_dbConnDefault;
}
