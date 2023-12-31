#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/Math.h"

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
		enum DSPEffects : uint8_t;

		class AudioSource
		{
		public:

			AudioSource(Transform* transform);
			~AudioSource();

			bool SetAudioClip(const SharedPtr<AudioClip>& clip);

			const SharedPtr<AudioClip>& GetClip();

			void PlayClip();

			void Update(float deltaTime);

			void RegisterSource();

			const float Get3DMinDist() const { return m_min3DDistance; }
			const float Get3DMaxDist() const { return m_max3DDistance; }

			void Set3DMinDist(const float newMin);
			void Set3DMaxDist(const float newMax);

			const int GetChannelIndex() const { return m_channelIndex; }

			void SetLoop(const bool loop);
			const bool GetLoop() const { return m_shouldLoop; }

			void AddDSPEffect(DSPEffects filter);

			void SetDSPState(DSPEffects filter, const bool isactive);

		protected:

			Vector3 CalculateVelocity(const float deltatime);

		protected:


			SharedPtr<AudioClip> m_audioClip = nullptr;

			bool m_shouldLoop = false;

			bool m_is3D = true;

			bool m_hasClip = false;



			// A useful Data pointer
			Transform* m_transform = nullptr;

			int m_channelIndex = -1;


			float m_volume = 1.0f;

			float m_rollOff = 1.0f;

			static int sourceCount;

			Vector3 lastPosition = Vector3(0.0f);


			float m_min3DDistance = 0.5f;
			float m_max3DDistance = 500.0f;

		};

		
	}
}

