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
    ViewModelTransactionHandler(QObject *parent, QQmlApplicationEngine *m_qmlEngine);
    ~ViewModelTransactionHandler();

    bool createModels(QObject *parent);
    void registerTypes();
    void connectModelsToView();
    bool connectSignals();

public slots:
    void onNewItemAddedSlot(const QString &msg);

private:
    QQmlApplicationEngine   *m_qmlEngine;
    IncomeOrderSQLModel     *m_dataModel;
    IncomeTypeModel         *m_typeModel;

};

#endif // VIEWMODELTRANSACTIONHANDLER_H
