#include "Human.h"
#include "UnitManager.h"

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

		

		UpdateMovement();

		
	

		if (DistanceSquared(GetPosition(), finalposition) < 1.0f)
		{
			MoveToNewPositionn();
		}

	}



	void Human::MoveToNewPositionn()
	{
		finalposition = UnitManager::GetRandomPosition();
		SetTargetDirection(finalposition);

	}


	bool Human::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{
		return false;
	}
}