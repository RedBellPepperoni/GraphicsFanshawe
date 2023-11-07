#include "BaseUnit.h"

namespace Robotron
{
	BaseUnit::BaseUnit()
	{


	}

	void BaseUnit::TakeDamage(const int damage)
	{
		if (m_health < damage)
		{
			//OnDeath();
		}
	}


	void BaseUnit::Update(float deltaTime)
	{
	}

	void BaseUnit::UpdateMovement()
	{


		if (!rigidBodyRef)
		{
			LOG_ERROR("No RigidBody Ref found");
			return;
		}


		if (LengthSquared(targetDirection) > 0.1f)
		{
			targetDirection = Normalize(targetDirection);
		}



		Vector3 resultingForce = Vector3(targetDirection.x, 0.0f, targetDirection.y) * speed * speedMultiplier ;

		rigidBodyRef->SetVelocity(resultingForce);

		

		//rigidBodyRef->SetForce(resultingForce);

		targetDirection = Vector2(0.0f);
	}

	void BaseUnit::SetTargetDirection(const Vector2& direction)
	{
		targetDirection = Normalize(direction);
	}


	void BaseUnit::SetSpeed(float newSpeed)
	{
		if (newSpeed <= 0)
		{
			return;
		}

		speed = newSpeed;
	}
	Vector2 BaseUnit::GetPosition() const
	{
		if (!rigidBodyRef)
		{
			LOG_ERROR("No RigidBody Ref found");
			return Vector2();
		}

		Vector3 position = rigidBodyRef->GetPosition();

		return Vector2(position.x, position.z);
	}


	void BaseUnit::SetCallBack()
	{
		rigidBodyRef->m_OnCollisionCallback = std::bind(&BaseUnit::OnCollision, this, placeholders::_1, placeholders::_2);
	}
}