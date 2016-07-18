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

int IncomeTypeModel::getIndexFromString(const QString &typeString) const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<IncomeType::asEnum>();
    return (IncomeType::asEnum)metaEnum.keysToValue(typeString.toStdString().c_str());
}

QHash<int, QByteArray> IncomeTypeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EnumRole] = "enum";

    return roles;
}
