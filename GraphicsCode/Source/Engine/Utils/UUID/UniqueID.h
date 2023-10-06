#pragma once
#include "uuid_v4.h"
#include "endianness.h"

namespace FanshaweGameEngine
{
	class UniqueID
	{

		UUIDv4::UUID m_uniqueID;

	public:

		UniqueID() {};
		UniqueID(const UUIDv4::UUID& id);

		const UUIDv4::UUID& GetId() const;

		std::string GetString() const;

		size_t GetHash() const;

		bool operator==(const UniqueID& other) const;
		bool operator!=(const UniqueID& other) const;

	};



	class UniqueIDGenerator
	{
		static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	public:


		static UniqueID GetNewID();
		static UniqueID GetNullID();




	};
}