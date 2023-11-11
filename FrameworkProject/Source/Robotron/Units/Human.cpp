#include "Human.h"
#include "UnitManager.h"
#include "Enemy.h"


namespace Robotron
{
	Human::Human(const HumanType type, RigidBody3D* body)
		: m_type(type)
	{
		rigidBodyRef = body;
		speed = 2.0f;
		speedMultiplier = 1.0f;

		shouldUpdate = true;
		MoveToNewPositionn();
	}


	void Human::Update(float deltaTime)
	{
		if (!shouldUpdate)
		{
			return;
		}

		SetTargetDirection(finalposition- GetPosition());

		rigidBodyRef->SetVelocity(Vector3(0.0f));

		//targetDirection = UnitManager::;

		SetFacingDirection();

		UpdateMovement();

		
	

		if (DistanceSquared(GetPosition(), finalposition) < 1.0f)
		{
			MoveToNewPositionn();
		}

		

		if (animatorRef)
		{
			
			switch (facingDirection)
			{
			case Robotron::FacingDirection::Top: animatorRef->PlayClip("Walk");
				break;
			case Robotron::FacingDirection::Left: animatorRef->PlayClip("WalkLeft");
				break;
			case Robotron::FacingDirection::Right: animatorRef->PlayClip("WalkRight");
				break;
			case Robotron::FacingDirection::Down: animatorRef->PlayClip("WalkBack");
				break;
			default:
				break;
			}
		}

		animatorRef->Update(deltaTime);

	}



	void Human::MoveToNewPositionn()
	{
		finalposition = UnitManager::GetRandomPosition();
		SetTargetDirection(finalposition);

	}


	bool Human::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{
		if (collided)
		{
			return false;
		}

		if (bodyTwo->m_tag == CollisionTag::Player)
		{
			Rescue();
		}


		else if (bodyTwo->m_tag == CollisionTag::Enemy)
		{
			ComponentView<RigidBody3D> view = Application::GetCurrent().GetCurrentScene()->GetEntityManager()->GetComponentsOfType<RigidBody3D>();

			for (Entity enemy : view)
			{
				if (&enemy.GetComponent<RigidBody3D>() == bodyTwo)
				{
					Enemy* enemyRef = enemy.TryGetComponent<Enemy>();


					if (enemyRef)
					{
						switch (enemyRef->GetType())
						{
						case Robotron::EnemyType::Grunt:

							break;

						case Robotron::EnemyType::Spheroid:

							break;
						case Robotron::EnemyType::Enforcer:

							break;

						case Robotron::EnemyType::Hulk:

							Die(false);

							collided = true;

							return false;
						default:
							break;
						}




						
					}
				}
			}


		}


		return false;
	}


	void Human::Die(bool becomeProg)
	{
		
		UnitManager::GetInstance().SetHumanDead(GetPosition(), becomeProg);
		collided = true;

		LOG_ERROR("{0}:{1} ", GetPosition().x, GetPosition().y);

		rigidBodyRef->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
		shouldUpdate = false;
	}


	void Human::Rescue()
	{
		rigidBodyRef->SetPosition(Vector3(100.0f, 0.0f, 100.0f));
		shouldUpdate = false;
		UnitManager::GetInstance().SetHumaRescued();
	}
}