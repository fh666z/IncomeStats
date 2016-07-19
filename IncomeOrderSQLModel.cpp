#include "IncomeOrderSQLModel.hpp"
#include <QSqlRecord>
#include <QFile>
#include <QMap>
#include <QDate>
#include <QDebug>


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
        for (int i = 0; i < rowCount(); ++i)
        {
            QVariantMap rec = get(i);

            foreach (QVariant value, rec)
            {
                if (QVariant::Date == value.type())
                {
                    exportFile.write(value.toDate().toString("yyyy-MM-dd").toUtf8());
                }
                else
                    exportFile.write(value.toByteArray());
                exportFile.write(",");
            }

            exportFile.write("\n");
        }

        exportFile.close();
    }
    else
        qDebug() << "Opening export file" << filePath << "failed!" << endl;

    return success;
}
