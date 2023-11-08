#include "ArenaImpl.h"
#include "Engine/Utils/Math/Random.h"

using namespace FanshaweGameEngine;

namespace Robotron
{
	ArenaImpl::ArenaImpl()
	{
	}
	ArenaImpl::~ArenaImpl()
	{
	}


	void ArenaImpl::Init(uint8_t width, uint8_t height)
	{
		// Assuiming the center is (0,0)

		TopRight = Vector2Int(width / 2, height / 2);
		BottomLeft = Vector2Int(-(width / 2), -(height / 2));

		// Seed the generator
		
		
		


	}

	uint8_t ArenaImpl::GetWidth() const
	{
		return m_width;
	}

	uint8_t ArenaImpl::GetHeight() const
	{
		return m_height;
	}

	Vector2 ArenaImpl::GetRandomPointinArena()
	{
		

		int randomX = Random32::Range.GetRandom(BottomLeft.x,TopRight.x);
		int randomY = Random32::Range.GetRandom(BottomLeft.y, TopRight.y);

		Vector2 targetLocation = Vector2(randomX, randomY);

		return targetLocation;
	}
	
}