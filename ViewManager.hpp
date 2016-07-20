#ifndef VIEWMODELTRANSACTIONHANDLER_H
#define VIEWMODELTRANSACTIONHANDLER_H

#include "IncomeType.hpp"

#include <QObject>
#include <QString>
#include <QDateTime>

class QQmlApplicationEngine;
class IncomeOrderSQLModel;


class ViewManager : public QObject
{
    Q_OBJECT

public:
    static ViewManager *getHandler();
    ~ViewManager();

    bool createModels(QObject *parent);
    void registerTypes();
    void connectModelsToView(QQmlApplicationEngine &qmlEngine);
    bool connectSignals(QQmlApplicationEngine &qmlEngine);

signals:
    Q_SIGNAL void notifyStatus(QString status);
    Q_SIGNAL void notifyError(QString errText = "", QString errDetailedText = "", bool shouldExit = false);

public slots:
    void onAcceptButtonPressed(int currentRow, QDateTime date, QString amount, QVariant type, QString comment);
    void onDeleteRowRequested(int currentRow);
    void onDbExportRequest(QString filePath);

protected:
    ViewManager(QObject *parent =    nullptr);

private:
    static ViewManager *m_dataHandler;

    IncomeOrderSQLModel     *m_dataModel;
    IncomeTypeModel         *m_typeModel;

};

#endif // VIEWMODELTRANSACTIONHANDLER_H
