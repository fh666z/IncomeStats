#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <QString>
#include <QDate>
#include <QDebug>

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
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

    QObject::connect(rootObj, SIGNAL(deleteRowRequested(int)),
                     this, SLOT(onDeleteRowRequested(int)));

    return true;
}

void ViewModelTransactionHandler::onAcceptOrderButtonPressed(int currentRow, QDateTime date,
                                                             QString amount, QVariant type,
                                                             QString comment)
{
    QSqlRecord rec(m_dataModel->record());
    rec.setGenerated("id", true);
    rec.setValue("date", date);
    rec.setValue("amount", amount.toDouble());
    rec.setValue("type", type);
    rec.setValue("comment", comment);

    bool res = m_dataModel->insertRecord(-1, rec);
    if (res)
    {
        m_dataModel->submitAll();
    }
}

void ViewModelTransactionHandler::onDeleteRowRequested(int currentRow)
{
    m_dataModel->removeRow(currentRow);
    m_dataModel->submitAll();
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
