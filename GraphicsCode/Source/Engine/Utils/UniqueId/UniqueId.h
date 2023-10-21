#pragma once
#include <stdint.h>


namespace FanshaweGameEngine
{
	class UniqueId
	{
	private:

		uint64_t m_uniqueId;

	public: 
		
		UniqueId();
		UniqueId(uint64_t uniqueId);
		UniqueId(const UniqueId& otherid);

		~UniqueId() = default;

		const uint64_t GetId() const
		{
			return m_uniqueId;
		}


	};
}


