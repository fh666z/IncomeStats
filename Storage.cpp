#include <QDebug>
#include <exception>

#include "Storage.hpp"

Storage* Storage::m_pDataStorage = nullptr;
StorageState Storage::m_state = StorageState::NotInitialized;

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
