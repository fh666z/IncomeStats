#include <QAbstractTableModel>

#include "IncomeOrderModel.hpp"


IncomeOrderModel::IncomeOrderModel(QObject *parent) : QAbstractListModel(parent)
{

}

void IncomeOrderModel::addIncomeOrder(const IncomeOrder &newOrder)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_incomeOrders << newOrder;
    endInsertRows();
}

int IncomeOrderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_incomeOrders.count();
}

QVariant IncomeOrderModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_incomeOrders.count())
        return QVariant();

    const IncomeOrder &order = m_incomeOrders[index.row()];
    switch(role)
    {
    case IdRole:
        return order.id();
        break;

    case AmountRole:
        return order.amount();
        break;

    case DateRole:
        return order.dateString();
        break;

    case TypeRole:
        return order.typeString();
        break;

    case CommentRole:
        return order.comment();
        break;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> IncomeOrderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[AmountRole] = "amount";
    roles[DateRole] = "date";
    roles[TypeRole] = "type";
    roles[CommentRole] = "comment";

    return roles;
}


