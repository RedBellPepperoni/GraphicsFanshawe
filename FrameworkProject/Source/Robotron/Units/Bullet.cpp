#include "Bullet.h"
#include "BulletPool.h"

namespace Robotron
{
	Bullet::Bullet(RigidBody3D* body)
	{
		rigidBodyRef = body;
		targetDirection = Vector2(0.0f);


		speed = 10.0f;
		speedMultiplier = 10.0f;

		if (body->m_tag == CollisionTag::Enemybullet)
		{
			speed = 2.0f;
			speedMultiplier = 7.0f;
			resetTimer = 6.0f;
		}

	}
	Bullet::~Bullet()
	{

	}

	void Bullet::SetTag(CollisionTag tag)
	{
		rigidBodyRef->m_tag = tag;

		if (tag == CollisionTag::Enemybullet)
		{
			tagtoHit = CollisionTag::Player;
		}
		else if (tag == CollisionTag::Playerbullet)
		{
			tagtoHit = CollisionTag::Enemy;
		}
		else
		{
			tagtoHit = CollisionTag::None;
		}
	}

	void Bullet::SetParentPool(BulletPool* parent)
	{
		parentPool = parent;
	}

	void Bullet::Update(float deltaTime)
	{
		if(!shouldUpdate)
		{
			return;
		}


		targetDirection = ShootingDir;

		UpdateMovement();

		counter = counter + deltaTime;

		if (counter >= resetTimer)
		{
			counter = 0.0f;
			collided = false;
			Reset();
			
		}

		

	}

	void Bullet::Shoot(Vector2 origin, Vector2 direction)
	{

		if (!parentPool)
		{
			return;
		}

		rigidBodyRef->SetStatic(false);

		collided = false;

		rigidBodyRef->SetPosition(Vector3(origin.x,0.0f,origin.y));


		ShootingDir = direction;
	
		shouldUpdate = true;
	}

	


	bool Bullet::GetFree() const
	{
		return isFree;
	}

	bool Bullet::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{
		if (!collided && (bodyTwo->m_tag == tagtoHit))
		{
			collided = true;
			Reset();
		
		}

		return false;
	}


	void Bullet::Reset()
	{
		rigidBodyRef->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
		rigidBodyRef->SetVelocity(Vector3(0.0f));
		rigidBodyRef->SetStatic(true);

		parentPool->PushToAvailable(this);
		shouldUpdate = false;
		ShootingDir = Vector2(0.0f);
	}
}