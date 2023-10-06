#include "UniqueID.h"

namespace FanshaweGameEngine
{
   UniqueID::UniqueID(const UUIDv4::UUID& id)
    {
        m_uniqueID = id;
    }



    const UUIDv4::UUID& UniqueID::GetId() const
    {
        return m_uniqueID;
    }

    std::string UniqueID::GetString() const
    {

        return m_uniqueID.str();
    }

    size_t UniqueID::GetHash() const
    {
        return  m_uniqueID.hash();
    }

    bool UniqueID::operator==(const UniqueID& other) const
    {
        return this->GetId() == other.GetId();
    }

    bool UniqueID::operator!=(const UniqueID& other) const
    {
        return !(*this == other);
    }

    UniqueID UniqueIDGenerator::GetNewID()
    {
  
        return UniqueID(uuidGenerator.getUUID());
    }

    UniqueID UniqueIDGenerator::GetNullID()
    {
        return UniqueID{ };
    }
}