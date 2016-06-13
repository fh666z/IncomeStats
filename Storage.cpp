#include <QDebug>
#include <exception>
#include <vector>

#include "Storage.hpp"

Storage* Storage::m_pDataStorage = nullptr;
StorageState Storage::m_state = StorageState::NotInitialized;
std::vector<IncomeOrder*> *Storage::m_incomeRecords = nullptr;

Storage *Storage::getStorage()
{
    if (m_pDataStorage == nullptr)
    {
        qDebug() << "Shouldn't be here!!!" << endl;
        throw ;
    }

    return m_pDataStorage;
}

bool Storage::exists()
{
    return (m_pDataStorage != nullptr);
}

StorageState Storage::getState()
{
    return m_state;
}

Storage::Storage()
{

}

Storage::~Storage()
{

}
