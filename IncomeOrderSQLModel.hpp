#ifndef INCOMEORDERSQLMODEL_H
#define INCOMEORDERSQLMODEL_H

#include <QSqlRelationalTableModel>


class IncomeOrderSQLModel : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    IncomeOrderSQLModel(QObject *parent = 0,  QSqlDatabase *db = new QSqlDatabase());
    ~IncomeOrderSQLModel();

private:
    QHash<int, QByteArray> roles;

public:
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void generateRoleNames();
    virtual bool select();
};

#endif // INCOMEORDERSQLMODEL_H
