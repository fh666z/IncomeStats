#ifndef INCOMEORDER_H
#define INCOMEORDER_H

#include <QObject>
#include <QDate>


class IncomeOrder : public QObject
{
    Q_OBJECT

//    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
//    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged)
//    Q_PROPERTY(IncomeType type READ type WRITE setType NOTIFY typeChanged)
//    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

public:
    enum class IncomeType {Salary, Bonus, Other};
    Q_ENUM(IncomeType)

    IncomeOrder();
    IncomeOrder(const IncomeOrder &rhs);
    IncomeOrder(int id);
    IncomeOrder(int id, double amount, QString date, QString type, QString comment);

    IncomeOrder& operator= (const IncomeOrder& rhs);


    int id() const;
    double amount() const;
    QDate date() const;
    QString dateString() const;
    IncomeType type() const;
    QString typeString() const;
    QString comment() const;

signals:
    void dateChanged(QDate date);
    void amountChanged(double amount);
    void typeChanged(QString type);
    void commentChanged(QString comment);

public slots:
    void setDate(QDate date);
    void setAmount(double amount);
    void setType(IncomeType type);
    void setType(QString type);
    void setComment(QString comment);
    void setId(unsigned id);

private:
    int m_id;
    double m_amount;
    QDate m_date;
    IncomeType m_type;
    QString m_comment;

};

#endif // INCOMEORDER_H
