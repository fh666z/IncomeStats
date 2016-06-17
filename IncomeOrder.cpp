#include <QMetaEnum>

#include "IncomeOrder.hpp"


IncomeOrder::IncomeOrder() : QObject()
{

}

IncomeOrder::IncomeOrder(const IncomeOrder &rhs) : QObject()
{
    m_id = rhs.id();
    m_amount = rhs.amount();
    m_date  = rhs.date();
    m_type = rhs.type();
    m_comment = rhs.comment();
}

IncomeOrder::IncomeOrder(int id) :
    m_id(id),
    m_amount(0),
    m_date(QDate::fromString("6-3-1988", "d-M-yyyy")),
    m_type(IncomeType::Other), m_comment("")
{

}

IncomeOrder::IncomeOrder(int id, double amount, QString date, QString type, QString comment) :
    m_id(id),
    m_amount(amount),
    m_date(QDate::fromString(date, "d-M-yyyy")),
    m_comment(comment)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<IncomeOrder::IncomeType>();
    m_type = (IncomeType)metaEnum.keysToValue(type.toStdString().c_str());
}

IncomeOrder &IncomeOrder::operator=(const IncomeOrder &rhs)
{
    m_id = rhs.id();
    m_amount = rhs.amount();
    m_date  = rhs.date();
    m_type = rhs.type();
    m_comment = rhs.comment();

    return *this;
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

int IncomeOrder::id() const
{
    return m_id;
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

void IncomeOrder::setType(IncomeOrder::IncomeType type)
{
    m_type = type;
}

void IncomeOrder::setType(QString type)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<IncomeOrder::IncomeType>();
    m_type = (IncomeType)metaEnum.keysToValue(type.toStdString().c_str());

    emit typeChanged(type);
}
void IncomeOrder::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(comment);
}

void IncomeOrder::setId(unsigned id)
{
    m_id = id;
}
