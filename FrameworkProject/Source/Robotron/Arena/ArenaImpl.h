#pragma once
#include "Engine/Utils/Math.h"

using namespace FanshaweGameEngine::Math;

namespace Robotron
{

	class ArenaImpl
	{

	public:

		ArenaImpl();
		~ArenaImpl();


		void Init(int levelId, uint8_t width, uint8_t height);

		void Update(float deltaTime);


		//Vector2 GetRandomPointinQuadrant(int quadarnt);

	private:

		uint8_t m_width;
		uint8_t m_height;

	};

}

