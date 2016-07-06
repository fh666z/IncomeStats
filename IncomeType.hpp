#ifndef INCOMETYPE_H
#define INCOMETYPE_H

#include <QObject>

class IncomeType : public QObject
{
    Q_OBJECT

public:
    explicit IncomeType(QObject *parent = 0);

    enum asEnum{
        Salary,
        Bonus,
        Other
    };
    Q_ENUM(asEnum)


};

#endif // INCOMETYPE_H
