#include "Player.h"

using namespace FanshaweGameEngine::Input;

namespace Robotron
{
	bool Player::OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
	{

		LOG_CRITICAL("Collided with ");
		return false;

	}


	void Player::Update(float deltaTime)
	{
		

		if (InputSystem::GetInstance().GetKeyHeld(Key::W))
		{
			targetDirection -= Vector2(0.0f, 1.0f);

			//LOG_INFO("Direction : X: {0}  Z:{1}", targetDirection.x, targetDirection.y);
			//LOG_INFO("DeltaTime : {0}", deltaTime);


		}

		
		if (InputSystem::GetInstance().GetKeyHeld(Key::S))
		{
			targetDirection += Vector2(0.0f, 1.0f) ;
		}

		
		if (InputSystem::GetInstance().GetKeyHeld(Key::A))
		{
			targetDirection -= Vector2(1.0f, 0.0f);
		}
			
	    if (InputSystem::GetInstance().GetKeyHeld(Key::D))
		{
			targetDirection += Vector2(1.0f, 0.0f);
		}



		//targetDirection = Normalize(targetDirection);

		UpdateMovement();

	}
}