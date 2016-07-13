#ifndef VIEWMODELTRANSACTIONHANDLER_H
#define VIEWMODELTRANSACTIONHANDLER_H

#include "IncomeType.hpp"

class QQmlApplicationEngine;
class IncomeOrderSQLModel;

class ViewModelTransactionHandler
{
public:
    static ViewModelTransactionHandler *getHandler();

    bool createModels(QObject *parent);
    void registerTypes();
    bool connectModelsToView(QQmlApplicationEngine &qmlEngine);

protected:
    ViewModelTransactionHandler();
    ~ViewModelTransactionHandler();

private:
    static ViewModelTransactionHandler *m_dataHandler;

    IncomeOrderSQLModel *m_dataModel;
    IncomeTypeModel     *m_typeModel;

};

#endif // VIEWMODELTRANSACTIONHANDLER_H
