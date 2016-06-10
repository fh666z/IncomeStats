#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <QString>

#include "Storage.hpp"

class QSaveFile;
class QJsonDocument;

class JSonStorage : public Storage
{
public:
    static void create();

    bool prepareStorage();
    bool open();
    bool close();

    bool writeRecord(IncomeOrder& new_order);
    IncomeOrder& readRecord();

    JSonStorage();
    virtual ~JSonStorage();

private:
    QSaveFile       *m_storageFile;
    QJsonDocument   *m_jsonDoc;

private:
    bool initFileHeader(auto flags);
    bool createJsonDocumentFromFile();
    QByteArray readJsonFromFile();
    bool checkHeader();
};

#endif // JSONSTORAGE_H
