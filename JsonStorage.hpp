#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <QString>
#include <QIODevice>

#include <vector>

#include "Storage.hpp"

class QFile;
class QJsonDocument;
class QJsonParseError;

class JSonStorage : public Storage
{
public:
    static void create();

    bool prepareStorage();
    bool open();
    bool close();

    void writeRecord(IncomeOrder* new_order);
    void writeRecord(int id, double amount, QString date, QString type, QString comment);

    IncomeOrder& readRecordByID(unsigned id) const;
    void readAllRecords(std::vector<IncomeOrder*> &recordsList) const;

    JSonStorage();
    virtual ~JSonStorage();

private:
    QFile           *m_storageFile;
    QJsonDocument   *m_jsonDoc;

private:
    void initHeader();
    bool checkHeader();
    bool extractAllRecords();
    bool verifyCreatedJson(QJsonParseError &error);
};

#endif // JSONSTORAGE_H
