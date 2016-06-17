#ifndef INCOMEORDERMODEL_H
#define INCOMEORDERMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractTableModel>

#include "IncomeOrder.hpp"


class IncomeOrderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IncomeOrderRoles {
        IdRole = Qt::UserRole + 1,
        AmountRole,
        DateRole,
        TypeRole,
        CommentRole
    };

    explicit IncomeOrderModel(QObject *parent = 0);

    void addIncomeOrder(const IncomeOrder &newOrder);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<IncomeOrder> m_incomeOrders;
};

#endif // INCOMEORDERMODEL_H
