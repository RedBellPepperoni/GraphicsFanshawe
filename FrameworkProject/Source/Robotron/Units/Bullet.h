#pragma once
#include "BaseUnit.h"

namespace Robotron
{

	class Bullet : public BaseUnit
	{
	public:

		Bullet();
		~Bullet();


		void Update(float deltaTime);

		void Shoot(Vector2 origin, Vector2 direction);

		bool GetFree() const;

	private:

		bool isFree = true;

		bool shouldUpdate = false;

		float resetTimer = 3.0f;

	};

}


