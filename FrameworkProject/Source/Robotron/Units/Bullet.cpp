#include "Bullet.h"

namespace Robotron
{
	Bullet::Bullet()
	{

	}
	Bullet::~Bullet()
	{

	}

	void Bullet::Update(float deltaTime)
	{
		if(!shouldUpdate)
		{
			return;
		}

		UpdateMovement();

	}

	void Bullet::Shoot(Vector2 origin, Vector2 direction)
	{
		isFree = false;

		rigidBodyRef->SetPosition(Vector3(origin.x,0.0f,origin.y));

		SetTargetDirection(direction);
	
		shouldUpdate = true;
	}




	bool Bullet::GetFree() const
	{
		return isFree;
	}
}