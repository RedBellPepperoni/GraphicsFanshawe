#include "Player.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "UnitManager.h"

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
		bulletpool->Init(20, CollisionTag::Playerbullet);

	}

	bool Player::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{
		if (bodyTwo->m_tag == CollisionTag::Enemy || bodyTwo->m_tag == CollisionTag::Enemybullet)
		{
			rigidBodyRef->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
			rigidBodyRef->SetVelocity(Vector3(0.0f));
			UnitManager::GetInstance().SetGameOver(false);
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

			
			animatorRef->PlayClip("WalkBack");

		}

		
		else if (InputSystem::GetInstance().GetKeyHeld(Key::S))
		{
			targetDirection += Vector2(0.0f, 1.0f) ;
			animatorRef->PlayClip("WalkFront");
		}

		
		if (InputSystem::GetInstance().GetKeyHeld(Key::A))
		{
			targetDirection -= Vector2(1.0f, 0.0f);
			animatorRef->PlayClip("WalkLeft");
		}
			
	    else if (InputSystem::GetInstance().GetKeyHeld(Key::D))
		{
			targetDirection += Vector2(1.0f, 0.0f);
			animatorRef->PlayClip("WalkRight");
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
			
			shootBackwards = true;
			
			if(isShooting)
			{
				shootBackwards = true;
			}
			

		}

		else
		{
			
			shootBackwards = false;
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

		animatorRef->Update(deltaTime);

	}


	void Player::Shoot()
	{
		Bullet* bullet = bulletpool->PushToActive();

		Vector2 finalDir = shootBackwards?  lastShootingDirection * -1.0f : lastShootingDirection;

		bullet->Shoot(GetPosition(), finalDir);

		//LOG_INFO("SHOT");
	}
}