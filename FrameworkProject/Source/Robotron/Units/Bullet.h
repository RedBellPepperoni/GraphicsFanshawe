#pragma once
#include "BaseUnit.h"

namespace Robotron
{

	class BulletPool;

	class Bullet : public BaseUnit
	{
	public:

		Bullet(RigidBody3D* body);
		~Bullet();

		void SetTag(CollisionTag tag);

		void SetParentPool(BulletPool* parent);

		void Update(float deltaTime) override;

		void Shoot(Vector2 origin, Vector2 direction);

		bool GetFree() const;

		bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) override;


	private:


		void Reset();

		bool isFree = true;

		bool shouldUpdate = false;

		float resetTimer = 2.0f;
		float counter = 0.0f;

		BulletPool* parentPool = nullptr;

		bool collided = false;

		Vector2 ShootingDir = Vector2(0.0f);

		CollisionTag tagtoHit = CollisionTag::None;

	};

}


