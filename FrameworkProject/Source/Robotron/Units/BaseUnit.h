#pragma once
#include "ICollidable.h"
#include "GameEngine.h"
#include "stdint.h"


using namespace FanshaweGameEngine::Physics;

namespace Robotron
{
	class UnitManager;
	

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

	protected:

		
		static int UnitCount;

		RigidBody3D* rigidBodyRef = nullptr;

		Vector2 targetDirection = Vector2(0.0f);

		
		float speedMultiplier = 10.0f;

		float speed = 1.0f;

	};
}
