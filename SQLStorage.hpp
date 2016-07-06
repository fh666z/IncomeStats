#ifndef SQLSTORAGE_H
#define SQLSTORAGE_H

#include <Storage.hpp>

class QSqlDatabase;

class SQLStorage : public Storage
{
public:
    static void create();

    bool prepareStorage();
    bool open();
    bool close();

    void writeRecord(IncomeOrder* new_order);
    void writeRecord(double amount, QString date, QString type, QString comment);

    IncomeOrder* readRecordByID(int id) const;
    std::vector<IncomeOrder *> *readAllRecords() const;

    SQLStorage();
    virtual ~SQLStorage();

    void* getConnection();

private:
    QSqlDatabase *m_dbConnDefault;

};

#endif // SQLSTORAGE_H
