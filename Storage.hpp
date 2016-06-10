#ifndef STORAGE_H
#define STORAGE_H

class IncomeOrder;
class QString;

enum class StorageState {NotInitialized, Prepared, Opened, Closed};

class Storage
{
public:
    static Storage* getStorage();
    static StorageState getState();

    bool exists();

    virtual bool prepareStorage() = 0;
    virtual bool open(QString init_string) = 0;
    virtual bool close() = 0;

    virtual bool writeRecord(IncomeOrder& new_order) = 0;
    virtual IncomeOrder& readRecord() = 0;


protected:
    Storage();
    virtual ~Storage();

    static StorageState    m_state;
    static Storage* m_pDataStorage;
};

#endif // STORAGE_H
