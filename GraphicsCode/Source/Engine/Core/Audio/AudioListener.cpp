#include "AudioListener.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "AudioManager.h"
#include "Engine/Utils/Logging/Log.h"

namespace FanshaweGameEngine
{
	namespace Audio
	{
		AudioListener::AudioListener(Transform* transform)
			:transformRef(transform)
		{
		}



		void AudioListener::Update(float deltaTime)
		{
			if (transformRef == nullptr)
			{
				return;
			}

			// Getting the actual forward vector
			Vector3 finalDirection = transformRef->GetRotation() * Vector3(0.0f, 0.0f, 1.0f);
			// Removing the Up/Down direction
			finalDirection.y = 0;

			// Sending the data to Audio manager;
			AudioManager::GetInstance().SetListenerAttributes(transformRef->GetPosition(), Vector3(0.0f), finalDirection, Vector3(0.0f, 1.0f, 0.0f));

		}



	}
}