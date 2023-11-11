#include "BaseUnit.h"
#include "UnitManager.h"

namespace Robotron
{
	BaseUnit::BaseUnit()
	{


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

		Vector3 resultingForce = Vector3(targetDirection.x, 0.0f, targetDirection.y) * speed * speedMultiplier;

		rigidBodyRef->SetVelocity(resultingForce);

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

	void BaseUnit::SetAnimtor(Animator* animator)
	{
		animatorRef = animator;
	}

	void BaseUnit::SetFacingDirection()
	{
		Vector2 normalizedDir = Normalize(targetDirection);

		if (normalizedDir.x >= 0.5)
		{
			facingDirection = FacingDirection::Right;
		}
		else if (normalizedDir.x <= -0.5)
		{
			facingDirection = FacingDirection::Left;
		}

		if (normalizedDir.y > 0.5f)
		{
			facingDirection = FacingDirection::Top;
		}
		else if (normalizedDir.y < -0.5f)
		{
			facingDirection = FacingDirection::Down;
		}
	}
}