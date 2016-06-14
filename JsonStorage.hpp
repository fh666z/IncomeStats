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
    void writeRecord(double amount, QString date, QString type, QString comment);

    IncomeOrder* readRecordByID(int id) const;
    std::vector<IncomeOrder *> *readAllRecords() const;

    JSonStorage();
    virtual ~JSonStorage();

private:
    QFile           *m_storageFile;

private:
    void initHeader(QJsonObject &headerObj);
    bool checkHeader(const QJsonDocument &doc);
    void extractAllRecords(const QJsonDocument &doc);
    bool verifyCreatedJson(const QJsonDocument &doc, QJsonParseError &error);
    void serializeRecordsToJson(QJsonDocument &doc);
};

#endif // JSONSTORAGE_H
