#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <QString>

#include "Storage.hpp"

class JSonStorage : public Storage
{
public:
    static void create();

    bool initialize(QString file_name);
    bool open();
    bool close();

    bool writeRecord(IncomeOrder& new_order);
    IncomeOrder& readRecord();

    JSonStorage();
    virtual ~JSonStorage();
protected:

};

#endif // JSONSTORAGE_H
