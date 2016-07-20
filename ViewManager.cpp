#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <QString>
#include <QDate>

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlError>

#include "ViewManager.hpp"
#include "Storage.hpp"
#include "SQLStorage.hpp"
#include "IncomeOrderSQLModel.hpp"
#include "IncomeType.hpp"

ViewManager *ViewManager::m_dataHandler = nullptr;

ViewManager *ViewManager::getHandler()
{
    if (m_dataHandler == nullptr)
        m_dataHandler = new ViewManager();

    return m_dataHandler;
}

bool ViewManager::createModels(QObject *parent)
{
    bool exists = Storage::getStorage()->exists();
    if (exists)
    {
        m_dataModel = new IncomeOrderSQLModel(parent, (QSqlDatabase *)(Storage::getStorage()->getConnection()));
        m_dataModel->setTable("records");
        m_dataModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        m_dataModel->select();

        m_typeModel = new IncomeTypeModel();

//        QDataWidgetMapper *mapper = new QDataWidgetMapper();
//        mapper->setModel(m_dataModel);
//        mapper->setItemDelegate(new QSqlRelationalDelegate());
    //    mapper->addMapping(nameEdit, model->fieldIndex("name"));
    //    mapper->addMapping(addressEdit, model->fieldIndex("address"));
    //    mapper->addMapping(typeComboBox, typeIndex);
//        mapper->toFirst();
    }

    return exists;
}

void ViewManager::registerTypes()
{
    qmlRegisterUncreatableType<IncomeType>("CPPEnums", 1, 0, "IncomeType", "Export enums from C++");
}

void ViewManager::connectModelsToView(QQmlApplicationEngine &qmlEngine)
{
    QQmlContext *qmlContext = qmlEngine.rootContext();

    qmlContext->setContextProperty("viewManagerClass", this);
    qmlContext->setContextProperty("incomeTypeModel", m_typeModel);
    qmlContext->setContextProperty("incomeOrderModel", m_dataModel);
}

bool ViewManager::connectSignals(QQmlApplicationEngine &qmlEngine)
{
    auto rootObjects = qmlEngine.rootObjects();
    if (rootObjects.count() < 1)
    {
        emit notifyError("Storage does NOT exist!", "", true);
        return false;
    }

    QObject *rootObj = rootObjects[0];

    QObject *orderView = rootObj->findChild<QObject*>("OrderViewObj");
    QObject::connect(orderView, SIGNAL(acceptButtonPressed(int, QDateTime, QString, QVariant, QString)),
                     this, SLOT(onAcceptButtonPressed(int, QDateTime, QString, QVariant, QString)));

    QObject::connect(rootObj, SIGNAL(deleteRowRequested(int)),  this, SLOT(onDeleteRowRequested(int)));
    QObject::connect(rootObj, SIGNAL(dbExportRequest(QString)), this, SLOT(onDbExportRequest(QString)));

    return true;
}

void ViewManager::onAcceptButtonPressed(int currentRow, QDateTime date,
                                                             QString amount, QVariant type,
                                                             QString comment)
{
    QSqlRecord rec(m_dataModel->record(currentRow));
    rec.setGenerated("id", true);
    rec.setValue("date", date);
    rec.setValue("amount", amount.toDouble());
    rec.setValue("type", type);
    rec.setValue("comment", comment);

    bool res = true;
    if (currentRow == -1)
        res &= m_dataModel->insertRecord(currentRow, rec);
    else
        res &= m_dataModel->setRecord(currentRow, rec);

    res &= m_dataModel->submitAll();

    if (res == false)
    {
        QString operation = "Editing";
        if (currentRow == -1)
            operation = "Adding";
        QString errMsg = "%1 record failed!";
        QString detailedErr = "File: %1 \nFunction: %2 \nLast error: %3";
        emit notifyError(errMsg.arg(operation),
                         detailedErr.arg( __FILE__ , __func__, m_dataModel->lastError().text()),
                         false);
    }
}

void ViewManager::onDeleteRowRequested(int currentRow)
{
    if ((currentRow >= 0) && (currentRow < m_dataModel->rowCount()))
    {
        QString message = "Delete Row: %1";
        emit notifyStatus(message.arg(currentRow));
        m_dataModel->removeRow(currentRow);
        m_dataModel->submitAll();
    }
    else
    {
        QString errMsg = "Cannot delete record %1!";
        QString detailedErr = "File: %1 \nFunction: %2";
        emit notifyError(errMsg.arg(currentRow), detailedErr.arg(__FILE__ , __func__), false);
    }
}

void ViewManager::onDbExportRequest(QString filePath)
{
    emit notifyStatus("Exporting to file: " + filePath + "...");

    bool success = m_dataModel->exportDataToFile(filePath);
    if (success)
        emit notifyStatus("Export successfull!");
    else
        emit notifyStatus("Export failed!");

}

ViewManager::ViewManager(QObject *parent) : QObject(parent)
{
    Q_UNUSED(parent)
    SQLStorage::create();
}

ViewManager::~ViewManager()
{
    Storage::getStorage()->close();

    delete m_typeModel;
    delete m_dataModel;
}
