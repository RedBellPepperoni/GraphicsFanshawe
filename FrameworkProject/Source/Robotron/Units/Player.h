#pragma once
#include "BaseUnit.h"

namespace Robotron
{


	class Player : public BaseUnit
	{
	public:

		Player(RigidBody3D* body) 
		{
			rigidBodyRef = body; 
			targetDirection = Vector2(0.0f);


			speed = 5.0f;
			speedMultiplier = 2.0f;
		
		};

		~Player() {};

		bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) override;
		
		void Update(float deltaTime) override;

	private:




	};
}

