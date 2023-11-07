#include "Player.h"
#include "BulletPool.h"
#include "Bullet.h"

using namespace FanshaweGameEngine::Input;

namespace Robotron
{
	



	Player::Player(RigidBody3D* body)
	{	
		rigidBodyRef = body;
		targetDirection = Vector2(0.0f);


		speed = 5.0f;
		speedMultiplier = 2.0f;


		bulletpool = Factory<BulletPool>::Create();
		bulletpool->Init(20);

	}

	bool Player::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{
		if (bodyTwo->m_tag == CollisionTag::Enemy)
		{
			LOG_CRITICAL("Collided with ");
		}
		
		return false;

	}


	void Player::Update(float deltaTime)
	{
		

		if (InputSystem::GetInstance().GetKeyHeld(Key::W))
		{
			targetDirection -= Vector2(0.0f, 1.0f);

			//LOG_INFO("Direction : X: {0}  Z:{1}", targetDirection.x, targetDirection.y);
			//LOG_INFO("DeltaTime : {0}", deltaTime);


		}

		
		if (InputSystem::GetInstance().GetKeyHeld(Key::S))
		{
			targetDirection += Vector2(0.0f, 1.0f) ;
		}

		
		if (InputSystem::GetInstance().GetKeyHeld(Key::A))
		{
			targetDirection -= Vector2(1.0f, 0.0f);
		}
			
	    if (InputSystem::GetInstance().GetKeyHeld(Key::D))
		{
			targetDirection += Vector2(1.0f, 0.0f);
		}
			
	    if (InputSystem::GetInstance().GetKeyHeld(Key::Space))
		{
				
			isShooting = true;			
			
		}

		else
		{

			
			if (LengthSquared(targetDirection) > 0.1f)
			{
				
				lastShootingDirection = targetDirection;
	
			}

			isShooting = false;
		}

		if (InputSystem::GetInstance().GetKeyHeld(Key::LeftControl))
		{
			
			flipShooting = true;
			
			if(isShooting)
			{
				flipShooting = true;
			}
			

		}

		else
		{
			
			flipShooting = false;
		}


		shootCounter += deltaTime;

		if(shootCounter >= shootCooldown)
		{
			canShoot = true;
		}


		if (canShoot && isShooting)
		{
			Shoot();
			shootCounter = 0.0f;
			canShoot = false;
		}
		
		

		//targetDirection = Normalize(targetDirection);

		UpdateMovement();

		bulletpool->Update(deltaTime);

	}


	void Player::Shoot()
	{
		Bullet* bullet = bulletpool->PushToActive();



		Vector2 finalDir = flipShooting?  lastShootingDirection * -1.0f : lastShootingDirection;

		bullet->Shoot(GetPosition(), finalDir);

		//LOG_INFO("SHOT");
	}
}