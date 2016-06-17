#ifndef STORAGE_H
#define STORAGE_H

#include <vector>

class IncomeOrder;
class QString;
class QJsonValue;

enum class StorageState {NotInitialized, Prepared, Opened, Closed};

class Storage
{
public:
    static Storage* getStorage();
    static StorageState getState();

    bool exists();

    virtual bool prepareStorage() = 0;
    virtual bool open() = 0;
    virtual bool close() = 0;

//    virtual void writeRecord(IncomeOrder* new_order) = 0;
    virtual void writeRecord(double amount, QString date, QString type, QString comment) = 0;
    virtual IncomeOrder* readRecordByID(int id) const = 0;
    virtual std::vector<IncomeOrder*> *readAllRecords() const = 0;

    int getRecordsCount() const;


protected:
    Storage();
    virtual ~Storage();

    static std::vector<IncomeOrder*> *m_incomeRecords;
    static StorageState              m_state;
    static Storage                   *m_pDataStorage;
    static int                       m_lastRecord;

};


#endif // STORAGE_H
