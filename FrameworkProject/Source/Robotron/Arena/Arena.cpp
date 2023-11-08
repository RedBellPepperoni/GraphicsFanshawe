#include "Arena.h"
#include "ArenaImpl.h"


namespace Robotron
{
    Arena* Arena::m_arenaPtr = nullptr;


    Arena::~Arena()
    {
        delete m_impl;
        delete m_arenaPtr;
    }

    void Arena::Init(uint8_t width, uint8_t height)
    {
        m_impl->Init(width, height);
    }

    Arena* Arena::GetArena(void)
    {

        if (!Arena::m_arenaPtr)
        {
            Arena::m_arenaPtr = new Arena();
        }
        return Arena::m_arenaPtr;
    }



    ArenaImpl* Arena::GetImp() const
    {
        return m_impl;
    }


    Arena::Arena()
    {
        m_impl = new ArenaImpl();
    }

}