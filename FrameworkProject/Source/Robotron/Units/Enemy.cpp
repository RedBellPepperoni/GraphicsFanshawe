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
		rigidBodyRef->SetVelocity(Vector3(0.0f));

		targetDirection = UnitManager::GetPlayerPos() - GetPosition();


		

		UpdateMovement();

		//LOG_INFO("{0}", LengthSquared(rigidBodyRef->GetVelocity()));
		


	}


}