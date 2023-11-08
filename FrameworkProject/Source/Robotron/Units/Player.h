#pragma once
#include "BaseUnit.h"

namespace Robotron
{
	class BulletPool;

	class Player : public BaseUnit
	{
	public:

		Player(RigidBody3D* body);

		~Player() {};

		bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) override;
		
		void Update(float deltaTime) override;


		void Shoot();

	private:

		SharedPtr<BulletPool> bulletpool;

		float shootCooldown = 0.15f;
		float shootCounter = 0.0f;
		bool canShoot;

		bool isShooting = false;
		bool shootBackwards = false;
		

		Vector2 lastShootingDirection = Vector2(1.0f, 0.0f);
	};
}

