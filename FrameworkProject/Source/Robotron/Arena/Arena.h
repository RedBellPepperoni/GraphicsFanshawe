#pragma once
#include <stdint.h>
namespace Robotron
{
	class ArenaImpl;

	class Arena
	{
	public:

		~Arena();


		void Init(uint8_t width, uint8_t height);

		static Arena* GetArena(void);

		ArenaImpl* GetImp() const;

	private:


		Arena();

		static Arena* m_arenaPtr;


		ArenaImpl* m_impl;
	};
}


