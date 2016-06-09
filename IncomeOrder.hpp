#ifndef INCOMEORDER_H
#define INCOMEORDER_H

#include <QObject>
#include <QDate>

enum class IncomeType {Salary, Bonus, Other};

class IncomeOrder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged)
    Q_PROPERTY(IncomeType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

    QDate m_date;
    double m_amount;
    IncomeType m_type;
    QString m_comment;

public:
    explicit IncomeOrder(QObject *parent = 0);

    QDate date() const;
    double amount() const;
    IncomeType type() const;
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

};

#endif // INCOMEORDER_H
