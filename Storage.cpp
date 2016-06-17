#include <QDebug>
#include <exception>
#include <vector>

#include "Storage.hpp"

Storage* Storage::m_pDataStorage = nullptr;
StorageState Storage::m_state = StorageState::NotInitialized;
std::vector<IncomeOrder*> *Storage::m_incomeRecords = nullptr;
int Storage::m_lastRecord = 0;


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

int Storage::getRecordsCount() const
{
    return m_lastRecord;
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
