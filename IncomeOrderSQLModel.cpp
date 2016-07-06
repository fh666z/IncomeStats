#include "IncomeOrderSQLModel.hpp"
#include <QSqlRecord>


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
