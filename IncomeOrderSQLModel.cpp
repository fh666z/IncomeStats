#include "IncomeOrderSQLModel.hpp"
#include <QSqlRecord>
#include <QFile>
#include <QMap>
#include <QDate>


IncomeOrderSQLModel::IncomeOrderSQLModel(QObject *parent, QSqlDatabase *db) :
    QSqlRelationalTableModel(parent, *db)
{

}

IncomeOrderSQLModel::~IncomeOrderSQLModel()
{

}

QVariant IncomeOrderSQLModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= rowCount())
        return QString();

    if (role < Qt::UserRole)
        return QSqlQueryModel::data(index, role);
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
}

QVariantMap IncomeOrderSQLModel::get(int idx) const {
    QVariantMap map;

    foreach(int k, roleNames().keys()) {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }

    return map;
}

void IncomeOrderSQLModel::generateRoleNames()
{
    roles.clear();

    for (int i = 0; i < record().count(); ++i)
    {
        roles[Qt::UserRole + i + 1] = record().fieldName(i).toUtf8();
    }
}

QHash<int, QByteArray> IncomeOrderSQLModel::roleNames() const
{
    return roles;
}

bool IncomeOrderSQLModel::select()
{
    bool ret = QSqlRelationalTableModel::select();

    if (ret)
        generateRoleNames();

    return ret;
}

bool IncomeOrderSQLModel::exportDataToFile(const QString &filePath)
{
    bool success = false;
    QString fileDesc(filePath);
    fileDesc.replace("file:///", "");
    QFile exportFile(fileDesc);

    success = exportFile.open(QIODevice::WriteOnly);
    if (success)
    {
        for (int rowIter = 0; rowIter < rowCount(); ++rowIter)
        {
            QVariantMap rec = get(rowIter);
            QVariantMap::const_iterator recIter = rec.begin();

            if (rowIter > 0)
                exportFile.write("\n");

            while (recIter != rec.end())
            {
                QString  fieldName = recIter.key();
                QVariant fieldValue = recIter.value();

                if (fieldName != "id")
                {
                    exportFile.write(fieldName.toUtf8());
                    exportFile.write(",");

                    if (QVariant::Date == fieldValue.type())
                    {
                        exportFile.write(fieldValue.toDate().toString("yyyy-MM-dd").toUtf8());
                    }
                    else
                        exportFile.write(fieldValue.toByteArray());
                    exportFile.write(",");
                }
                recIter++;
            }
        }

        exportFile.close();
    }
    else
        qDebug() << "Opening export file" << filePath << "failed!" << endl;

    return success;
}

bool IncomeOrderSQLModel::importDataFromFile(const QString &filePath)
{
    bool success = false, res = true;
    QString fileDesc(filePath);
    fileDesc.replace("file:///", "");
    QFile importFile(fileDesc);

    success = importFile.open(QIODevice::ReadOnly);
    if (success)
    {
        QByteArray fileData = importFile.readAll();
        QList<QByteArray> recordsList = fileData.split('\n');

        foreach(QByteArray currRecord, recordsList)
        {
            QList<QByteArray> fieldsWithValue = currRecord.split(',');
            QList<QByteArray>::const_iterator itemIter = fieldsWithValue.begin();

            if (fieldsWithValue.begin() != fieldsWithValue.end())
            {
                QSqlRecord rec(record(-1));
                rec.setGenerated("id", true);
                while (itemIter != fieldsWithValue.end())
                {
                    if (*itemIter == "")
                        break;

                    QString fieldName = *itemIter;
                    itemIter++;
                    QString fieldValue = *itemIter;
                    itemIter++;

                    rec.setValue(fieldName, fieldValue);
                }

                res &= insertRecord(-1, rec);
                res &= submitAll();
            }
        }
    }

    return success & res;
}


