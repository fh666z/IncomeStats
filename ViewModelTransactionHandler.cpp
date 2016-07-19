#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <QException>
#include <QString>
#include <QDate>
#include <QDebug>

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlError>
#include <QDataWidgetMapper>

#include "ViewModelTransactionHandler.hpp"

#include "Storage.hpp"
#include "SQLStorage.hpp"
#include "IncomeOrderSQLModel.hpp"

#include "IncomeType.hpp"

ViewModelTransactionHandler *ViewModelTransactionHandler::m_dataHandler = nullptr;

ViewModelTransactionHandler *ViewModelTransactionHandler::getHandler()
{
    if (m_dataHandler == nullptr)
        m_dataHandler = new ViewModelTransactionHandler();

    return m_dataHandler;
}

bool ViewModelTransactionHandler::createModels(QObject *parent)
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

void ViewModelTransactionHandler::registerTypes()
{
    qmlRegisterUncreatableType<IncomeType>("CPPEnums", 1, 0, "IncomeType", "Export enums from C++");
}

void ViewModelTransactionHandler::connectModelsToView(QQmlApplicationEngine &qmlEngine)
{
    QQmlContext *qmlContext = qmlEngine.rootContext();

    qmlContext->setContextProperty("incomeTypeModel", m_typeModel);
    qmlContext->setContextProperty("incomeOrderModel", m_dataModel);
}

bool ViewModelTransactionHandler::connectSignals(QQmlApplicationEngine &qmlEngine)
{
    auto rootObjects = qmlEngine.rootObjects();
    if (rootObjects.count() < 1)
        return false;
    QObject *rootObj = rootObjects[0];

    QObject::connect(rootObj, SIGNAL(orderViewAcceptButtonPressed(int, QDateTime, QString, QVariant, QString)),
                     this, SLOT(onAcceptOrderButtonPressed(int, QDateTime, QString, QVariant, QString)));

    QObject::connect(rootObj, SIGNAL(deleteRowRequested(int)), this, SLOT(onDeleteRowRequested(int)));
    QObject::connect(rootObj, SIGNAL(dbExportRequest(QString)), this, SLOT(onDbExportRequest(QString)));


    return true;
}

void ViewModelTransactionHandler::onAcceptOrderButtonPressed(int currentRow, QDateTime date,
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
        qDebug() << "File: " __FILE__ << "function:" << __func__ << "Adding record failed!" << endl;
        qDebug() << "Last SQL Error:" << m_dataModel->lastError() << endl;
    }
}

void ViewModelTransactionHandler::onDeleteRowRequested(int currentRow)
{
    if ((currentRow >= 0) && (currentRow < m_dataModel->rowCount()))
    {
        qDebug() << "Delete Row: " << currentRow << endl;
        m_dataModel->removeRow(currentRow);
        m_dataModel->submitAll();
    }
    else
        qDebug() << "File: " __FILE__ << "function:" << __func__ << "Cannot delete row:" << currentRow << endl;
}

void ViewModelTransactionHandler::onDbExportRequest(QString filePath)
{
    qDebug() << "Exporting to file: " << filePath << "..." << endl;
    bool success = m_dataModel->exportDataToFile(filePath);
    if (success)
        qDebug() << "Export successfull!" << endl;
    else
        qDebug() << "Export failed!" << endl;

}

ViewModelTransactionHandler::ViewModelTransactionHandler(QObject *parent) :
    QObject(parent)
{
    Q_UNUSED(parent)
    SQLStorage::create();
}

ViewModelTransactionHandler::~ViewModelTransactionHandler()
{
    Storage::getStorage()->close();

    delete m_typeModel;
    delete m_dataModel;
}
