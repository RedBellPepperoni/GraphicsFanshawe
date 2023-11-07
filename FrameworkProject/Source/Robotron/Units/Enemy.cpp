#include "Enemy.h"

namespace Robotron
{

	Enemy::Enemy(const EnemyType type, RigidBody3D* body)
		: m_type(type)
	{
		rigidBodyRef = body;
		speed = 1.0f;
		speedMultiplier = 5.0f;
	}


	void Enemy::Update(float deltaTime)
	{
		if (!shouldUpdate)
		{
			return;
		}


		rigidBodyRef->SetVelocity(Vector3(0.0f));

		targetDirection = UnitManager::GetPlayerPos() - GetPosition();


		

		UpdateMovement();

		//LOG_INFO("{0}", LengthSquared(rigidBodyRef->GetVelocity()));
		


	}

	bool Enemy::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{

		if (bodyTwo->m_tag == CollisionTag::Playerbullet)
		{
			shouldUpdate = false;

			rigidBodyRef->SetPosition(Vector3(200.0f, 0.0f, 100.0f));

		}


		return false;
	}


}