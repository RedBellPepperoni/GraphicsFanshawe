#include "AudioSource.h"
#include "AudioManager.h"
#include "Engine/Core/ECS/Components/Transform.h"

namespace FanshaweGameEngine
{
	using namespace Components;


	namespace Audio
	{
		AudioSource::AudioSource(Transform* trasnform)
		{
			m_transform = trasnform;
		}

		AudioSource::~AudioSource()
		{

		}

		bool AudioSource::SetAudioClip(const SharedPtr<AudioClip>& clip)
		{
			m_audioClip = clip;

			AudioManager::GetInstance().LoadSound(*clip, AudioManager::SoundType::Sound3D);
			//AudioManager::GetInstance().


			return false;
		}

		const SharedPtr<AudioClip>& AudioSource::GetClip()
		{
			return m_audioClip;
		}


		void AudioSource::PlayClip()
		{
			int channelId = AudioManager::GetInstance().PlaySound(*GetClip());
			AudioManager::GetInstance().SetClip3DAttributes(channelId ,m_transform->GetPosition(),Vector3(0.0f));

		}

		void AudioSource::Update(float deltaTime)
		{

		}
	}
}