#include "Arena.h"
#include "ArenaImpl.h"


namespace Robotron
{
    Arena* Arena::m_arenaPtr = nullptr;


    Arena::~Arena()
    {

    }

    void Arena::Init(int levelId, uint8_t width, uint8_t height)
    {


    }

    Arena* Arena::GetArena(void)
    {

        if (!Arena::m_arenaPtr)
        {
            Arena::m_arenaPtr = new Arena();
        }
        return Arena::m_arenaPtr;
    }


    Arena::Arena()
    {

        m_impl = new ArenaImpl();
    }

}