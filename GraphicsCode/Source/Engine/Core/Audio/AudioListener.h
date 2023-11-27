#pragma once
#include "Engine/Utils/Math.h"


namespace FanshaweGameEngine
{
	
	namespace Components
	{
		class Transform;
	}

	using namespace Components;

	namespace Audio
	{


		class AudioListener
		{


		public:

			AudioListener(Transform* transform);
			~AudioListener() = default;



			void Update(float deltaTime);

		private:


			Transform* transformRef = nullptr;

		};


	}
}

