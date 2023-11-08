#pragma once
#include "BaseUnit.h"
#include "UnitManager.h"


namespace Robotron
{
	enum class HumanType : uint8_t
	{
		None,
		Daddy,
		Mommy,
		Mikey
	};

	class Human : public BaseUnit
	{

	public:

		Human(const HumanType type, RigidBody3D* body);
		~Human() {};

		void Update(float deltaTime) override;

		

		void MoveToNewPositionn();

		bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) override;


		void Die(bool becomeProg);
		void Rescue();

	private:


		HumanType m_type;

		Vector2 finalposition = Vector2(0.0f);

		UnitManager* manager = nullptr;
		
		bool collided = false;

		bool shouldUpdate = true;
	};
}

