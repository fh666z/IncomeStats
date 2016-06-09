#include "IncomeOrder.hpp"


IncomeOrder::IncomeOrder(QObject *parent) : QObject(parent)
{

}

//=====================================================================================================================
// Getters
QDate IncomeOrder::date() const
{
    return m_date;
}

double IncomeOrder::amount() const
{
    return m_amount;
}

IncomeType IncomeOrder::type() const
{
    return m_type;
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
