#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <QString>

#include "Storage.hpp"

class QFile;
class QJsonDocument;

class JSonStorage : public Storage
{
public:
    static void create();

    bool prepareStorage();
    bool open(QString file_name);
    bool close();

    bool writeRecord(IncomeOrder& new_order);
    IncomeOrder& readRecord();

    JSonStorage();
    virtual ~JSonStorage();

private:
    bool initFileHeader();

private:
    QFile           *m_storage_file;
    QJsonDocument   *m_json_doc;

    void createJsonDocument();
};

#endif // JSONSTORAGE_H
