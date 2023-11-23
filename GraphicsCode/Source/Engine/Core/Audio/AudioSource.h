#pragma once
#include "Engine/Core/Memory/Memory.h"

namespace FanshaweGameEngine
{
	namespace Components
	{
		class Transform;
	}

	using Components::Transform;

	

	namespace Audio
	{
		struct AudioClip;
		class AudioManager;

		class AudioSource
		{
		public:

			AudioSource(Transform* transform);
			~AudioSource();

			bool SetAudioClip(const SharedPtr<AudioClip>& clip);

			const SharedPtr<AudioClip>& GetClip();

			void PlayClip();

			void Update(float deltaTime);


		protected:

			SharedPtr<AudioClip> m_audioClip = nullptr;

			bool m_shouldLoop = false;

			bool m_is3D = true;

			bool m_hasClip = false;

			// A useful Data pointer
			Transform* m_transform = nullptr;


			float m_volume = 1.0f;

			float m_rollOff = 1.0f;

		};

		
	}
}

