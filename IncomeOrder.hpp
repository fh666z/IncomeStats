#ifndef INCOMEORDER_H
#define INCOMEORDER_H

#include <QObject>
#include <QDate>


class IncomeOrder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(IncomeType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

public:
    enum class IncomeType {Salary, Bonus, Other};
    Q_ENUM(IncomeType)

    explicit IncomeOrder(QObject *parent = 0);
    IncomeOrder(double amount, QString date, IncomeType type, QString comment);

    QDate date() const;
    QString dateString() const;
    double amount() const;
    IncomeType type() const;
    QString typeString() const;
    QString comment() const;

signals:
    void dateChanged(QDate date);
    void amountChanged(double amount);
    void typeChanged(IncomeType type);
    void commentChanged(QString comment);

public slots:
    void setDate(QDate date);
    void setAmount(double amount);
    void setType(IncomeType type);
    void setComment(QString comment);

private:
    double m_amount;
    QDate m_date;
    IncomeType m_type;
    QString m_comment;

};

#endif // INCOMEORDER_H
