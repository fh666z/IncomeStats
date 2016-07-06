#include "IncomeType.hpp"
#include <QMetaEnum>

IncomeType::IncomeType(QObject *parent) : QObject(parent)
{

}



IncomeTypeModel::IncomeTypeModel(QObject *parent) : QAbstractListModel(parent)
{

}

int IncomeTypeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return IncomeType::getEnumElementsNumber();
}

QVariant IncomeTypeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= IncomeType::getEnumElementsNumber())
        return QVariant();

    if (role == EnumRole)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<IncomeType::asEnum>();
        return metaEnum.valueToKey((int)index.row());
    }
    else
        return QVariant();

}

QHash<int, QByteArray> IncomeTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EnumRole] = "enum";

    return roles;
}
