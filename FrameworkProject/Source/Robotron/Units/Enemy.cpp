#include "Enemy.h"
#include "Bullet.h"
namespace Robotron
{

	Enemy::Enemy(const EnemyType type, RigidBody3D* body)
	{

		m_type = type;
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

	EnemyType& Enemy::GetType()
	{
		return m_type;
	}

	bool Enemy::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{

		if (bodyTwo->m_tag == CollisionTag::Playerbullet)
		{
			// If its a hulk, dont kill it just move it away from the player
			if (m_type == EnemyType::Hulk)
			{
				Vector2 direction = (GetPosition() - UnitManager::GetPlayerPos());

				direction = Normalize(direction) * 25.0f;
				//rigidBodyRef->SetForce(Vector3(direction.x,0.0f,direction.y));
				rigidBodyRef->SetVelocity(Vector3(direction.x,0.0f,direction.y));

			}
			else
			{
				shouldUpdate = false;
				rigidBodyRef->SetPosition(Vector3(200.0f, 0.0f, 100.0f));
			}

			

		}


		return false;
	}

	


}