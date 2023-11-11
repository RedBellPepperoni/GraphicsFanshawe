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

		if (m_type == EnemyType::Enforcer)
		{
			bulletPool = Factory<BulletPool>::Create();
			bulletPool->Init(5, CollisionTag::Enemybullet);
		}
		


	}


	void Enemy::Update(float deltaTime)
	{
		if (!shouldUpdate)
		{
			return;
		}

		if (m_type == EnemyType::Enforcer)
		{
			shootCounter += deltaTime;

			if (shootCounter >= shootCooldown)
			{
				OnShoot();

				shootCounter = 0.0f;
			}


			bulletPool->Update(deltaTime);
		}



	

		rigidBodyRef->SetVelocity(Vector3(0.0f));

		targetDirection = UnitManager::GetPlayerPos() - GetPosition();

		SetFacingDirection();

		UpdateMovement();

		

		
		if (animatorRef)
		{
			switch (m_type)
			{
			case Robotron::EnemyType::Grunt: animatorRef->PlayClip("Walk");
				break;
			case Robotron::EnemyType::Spheroid:
				break;
			case Robotron::EnemyType::Enforcer:
				break;
			case Robotron::EnemyType::Hulk:

				switch (facingDirection)
				{
				case Robotron::FacingDirection::Down:
				case Robotron::FacingDirection::Top: animatorRef->PlayClip("Walk");
					break;
				case Robotron::FacingDirection::Left: animatorRef->PlayClip("WalkLeft");
					break;
				case Robotron::FacingDirection::Right: animatorRef->PlayClip("WalkRight");

					break;
				
		
				default:
					break;
				}

				break;
			case Robotron::EnemyType::Brain:
				break;
			default:
				break;
			}

			animatorRef->Update(deltaTime);
		}

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
				if (m_type == EnemyType::Enforcer)
				{
					bulletPool->RestAll();
				}


				UnitManager::GetInstance().EnemyKilled(m_type);

				shouldUpdate = false;
				rigidBodyRef->SetPosition(Vector3(200.0f, 0.0f, 100.0f));



			}

			

		}


		return false;
	}

	

	void Enemy::OnShoot()
	{

		Bullet* bullet = bulletPool->PushToActive();

		Vector2 finalDir = Normalize(UnitManager::GetInstance().GetPlayerPos() - GetPosition());

		bullet->Shoot(GetPosition(), finalDir);

	}

	


}