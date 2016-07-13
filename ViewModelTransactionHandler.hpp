#ifndef VIEWMODELTRANSACTIONHANDLER_H
#define VIEWMODELTRANSACTIONHANDLER_H

#include "IncomeType.hpp"

class QObject;
class QQmlApplicationEngine;
class IncomeOrderSQLModel;


class ViewModelTransactionHandler //: public QObject
{
    //Q_OBJECT

public:
    static ViewModelTransactionHandler *getHandler();

    bool createModels(QObject *parent);
    void registerTypes();
    void connectModelsToView(QQmlApplicationEngine &qmlEngine);

public slots:
    void newItemAddedSlot(const QString &msg);

private:
    ViewModelTransactionHandler(QObject *parent = nullptr);
    ~ViewModelTransactionHandler();

private:
    static ViewModelTransactionHandler *m_dataHandler;

    IncomeOrderSQLModel *m_dataModel;
    IncomeTypeModel     *m_typeModel;

};

#endif // VIEWMODELTRANSACTIONHANDLER_H
