#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <QSqlRelationalDelegate>
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

        QDataWidgetMapper *mapper = new QDataWidgetMapper();
        mapper->setModel(m_dataModel);
        mapper->setItemDelegate(new QSqlRelationalDelegate());
    //    mapper->addMapping(nameEdit, model->fieldIndex("name"));
    //    mapper->addMapping(addressEdit, model->fieldIndex("address"));
    //    mapper->addMapping(typeComboBox, typeIndex);
        mapper->toFirst();
    }

    return exists;
}

void ViewModelTransactionHandler::registerTypes()
{
    qmlRegisterUncreatableType<IncomeType>("CPPEnums", 1, 0, "IncomeType", "Export enums from C++");
}

bool ViewModelTransactionHandler::connectModelsToView(QQmlApplicationEngine &qmlEngine)
{
    QQmlContext *qmlContext = qmlEngine.rootContext();

    qmlContext->setContextProperty("incomeTypeModel", m_typeModel);
    qmlContext->setContextProperty("incomeOrderModel", m_dataModel);

    return true;
}

ViewModelTransactionHandler::ViewModelTransactionHandler()
{
    SQLStorage::create();
}

ViewModelTransactionHandler::~ViewModelTransactionHandler()
{
    Storage::getStorage()->close();

    delete m_typeModel;
    delete m_dataModel;
}
