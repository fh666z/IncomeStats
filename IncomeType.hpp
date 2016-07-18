#ifndef INCOMETYPE_H
#define INCOMETYPE_H

#include <QObject>
#include <QAbstractListModel>

class IncomeType : public QObject
{
    Q_OBJECT

public:
    explicit IncomeType(QObject *parent = 0);

    enum asEnum{
        Salary,
        Bonus,
        Other,
        ElementsCount
    };
    Q_ENUM(asEnum)

    static int getEnumElementsNumber() { return asEnum::ElementsCount;};
};

class IncomeTypeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum IncomeTypeRoles{
        EnumRole = Qt::UserRole + 1,
    };

    explicit IncomeTypeModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE int getIndexFromString(const QString &typeString) const;

protected:
    QHash<int, QByteArray> roleNames() const;

};

#endif // INCOMETYPE_H
