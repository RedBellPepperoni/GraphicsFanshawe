#include "CollisionSystem.h"

#include <vector>


void CollisionSystem::Update()
{
}

void CollisionSystem::CheckOtherRobotCollisions(Robot& bot, Transform& transform, MeshRenderer& meshRend)
{
	
	entt::registry& registry = Application::GetCurrent().GetCurrentScene()->GetRegistry();

	// havent wrapped all the Entt functions into my calsses , so the current state looks like this

	auto robotView = registry.view<Robot>();
	auto transformView = registry.view<Transform>();
	auto meshRendererView = registry.view<MeshRenderer>();

	Vector3 position = transform.GetPosition();


	// Looping through all the entities that have the Robot component
	for (entt::entity robot : robotView)
	{
		Transform* othertransform = &transformView.get<Transform>(robot);
		MeshRenderer* material = &meshRendererView.get<MeshRenderer>(robot);

		Robot* otherbot = &robotView.get<Robot>(robot);

		// Ignore the robot chekcing with iteself
		if (otherbot == &bot)
		{
			continue;
		}

		float distance = Distance(position, othertransform->GetPosition());

		// Collision Occurs
		if( distance < m_collisionRadius)
		{
			//LOG_CRITICAL("COLIISION");

			int friendId = bot.GetFriendId();
			int otherId = otherbot->GetId();

			if (friendId == otherId)
			{
				//LOG_INFO("==== FRIEND FOUND ==== {0} : {1}",bot.GetId(), otherId);

				bot.OnAction(otherId, Framework::IDetector::ActionType::GreetFriend);
				
				material->GetMaterial()->albedoColour = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
				meshRend.GetMaterial()->albedoColour = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

				
			

				if (!bot.m_Greeted)
				{
					bot.SetShouldMove(false);
					otherbot->SetShouldMove(false);

					otherbot->currentCooldown = 1.0f;
					bot.currentCooldown = 1.0f;

					bot.m_Greeted = true;
					otherbot->m_Greeted = true;




				}
				
			}

			


		}

		/*if (bot.m_Greeted)
		{
			bot.currentCooldown = bot.currentCooldown - 0.05f;

			if (bot.currentCooldown < 0)
			{
				bot.currentCooldown = 1.0f;
				bot.m_Greeted = false;

				meshRend.GetMaterial()->albedoColour = Vector4(0.0f,0.0f,0.0f,1.0f);
			}
		}*/

		

	}


}
