#pragma once
#include "ICollidable.h"
#include "GameEngine.h"
#include "stdint.h"
#include "Robotron/Animation/Animator.h"

using namespace FanshaweGameEngine::Physics;

namespace Robotron
{
	class UnitManager;
	
	enum class FacingDirection : uint8_t
	{
		Top,
		Left,
		Right,
		Down
	};


	class BaseUnit : public ICollidable
	{
	public:
		BaseUnit();
	
		virtual  ~BaseUnit() = default;


		virtual void Update(float deltaTime);

		virtual void UpdateMovement();

		virtual void SetTargetDirection(const Vector2& direction);

		

		void SetSpeed(float newSpeed);

		Vector2 GetPosition() const;


		void SetCallBack();

		virtual bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) override { return false; };


		virtual void SetAnimtor(Animator* animator);


	protected:

		virtual void SetFacingDirection();

	protected:

		
		static int UnitCount;

		RigidBody3D* rigidBodyRef = nullptr;

		Vector2 targetDirection = Vector2(0.0f);

		Animator* animatorRef = nullptr;

		FacingDirection facingDirection;
		
		float speedMultiplier = 10.0f;

		float speed = 1.0f;

	};
}
