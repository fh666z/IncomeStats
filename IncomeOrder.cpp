#include <QMetaEnum>

#include "IncomeOrder.hpp"



IncomeOrder::IncomeOrder(QObject *parent) : QObject(parent)
{

}

IncomeOrder::IncomeOrder(double amount, QString date, IncomeOrder::IncomeType type, QString comment) :
    m_amount(amount), m_date(QDate::fromString(date, "d-M-yyyy")), m_type(type), m_comment(comment)
{
}

//=====================================================================================================================
// Getters
QDate IncomeOrder::date() const
{
    return m_date;
}

QString IncomeOrder::dateString() const
{
    return m_date.toString("dd-MM-yyyy");
}

double IncomeOrder::amount() const
{
    return m_amount;
}

IncomeOrder::IncomeType IncomeOrder::type() const
{
    return m_type;
}

QString IncomeOrder::typeString() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<IncomeOrder::IncomeType>();
    return metaEnum.valueToKey((int)m_type);
}

QString IncomeOrder::comment() const
{
    return m_comment;
}


//=====================================================================================================================
// Setters
void IncomeOrder::setDate(QDate date)
{
    if (m_date == date)
        return;

    m_date = date;
    emit dateChanged(date);
}
void IncomeOrder::setAmount(double amount)
{
    if (m_amount == amount)
        return;

    m_amount = amount;
    emit amountChanged(amount);
}
void IncomeOrder::setType(IncomeType type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}
void IncomeOrder::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(comment);
}
