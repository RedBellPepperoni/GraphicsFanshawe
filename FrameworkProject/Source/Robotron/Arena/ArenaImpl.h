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


		void Init(uint8_t width, uint8_t height);


		uint8_t GetWidth() const;
		uint8_t GetHeight() const;


		Vector2 GetRandomPointinArena();
		

	private:


		void AddQuadrant();

		uint8_t m_width;
		uint8_t m_height;

		Vector2Int TopRight;
		Vector2Int BottomLeft;

		

	};

}

