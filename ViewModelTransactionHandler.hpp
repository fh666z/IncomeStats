#ifndef VIEWMODELTRANSACTIONHANDLER_H
#define VIEWMODELTRANSACTIONHANDLER_H

#include "IncomeType.hpp"

class QObject;
class QQmlApplicationEngine;
class IncomeOrderSQLModel;


class ViewModelTransactionHandler : public QObject
{
    Q_OBJECT

public:
    static ViewModelTransactionHandler *getHandler();
    ~ViewModelTransactionHandler();

    bool createModels(QObject *parent);
    void registerTypes();
    void connectModelsToView(QQmlApplicationEngine &qmlEngine);
    bool connectSignals(QQmlApplicationEngine &qmlEngine);

public slots:
    void onNewItemAddedSlot(const QString &msg);

protected:
    ViewModelTransactionHandler(QObject *parent = nullptr);

private:
    static ViewModelTransactionHandler *m_dataHandler;

    IncomeOrderSQLModel     *m_dataModel;
    IncomeTypeModel         *m_typeModel;

};

#endif // VIEWMODELTRANSACTIONHANDLER_H
