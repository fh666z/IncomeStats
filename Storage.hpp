#ifndef STORAGE_H
#define STORAGE_H

class IncomeOrder;
class QString;

class Storage
{
public:
    static Storage* getStorage();

    bool exists();

    virtual bool initialize(QString init_string) = 0;
    virtual bool open() = 0;
    virtual bool close() = 0;

    virtual bool writeRecord(IncomeOrder& new_order) = 0;
    virtual IncomeOrder& readRecord() = 0;

protected:
    Storage();
    virtual ~Storage();

    static Storage* m_pDataStorage;
};

#endif // STORAGE_H
