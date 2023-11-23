#include "AudioManager.h"
#include <fmod_errors.h>
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{

	namespace Audio
	{
		FMOD::System* AudioManager::m_audiosystem = nullptr;


		FMOD_VECTOR GetFmodVector(const Vector3& glmVector)
		{
			FMOD_VECTOR vector;

			vector.x = glmVector.x;
			vector.y = glmVector.y;
			vector.z = glmVector.z;

			return vector;
		}

		Vector3 GetGlmVector(const FMOD_VECTOR& fmodVector)
		{
			return Vector3(fmodVector.x, fmodVector.y, fmodVector.z);
		}


		std::string& ErrorCheckFMod(FMOD_RESULT result, int line)
		{
			// There is some Actual FMOD API error which is Real Bad
			if (result != FMOD_OK)
			{

				std::string errorMsg = "FMOD ERROR: AudioManager [Line : " + std::to_string(line) + "] " + std::to_string(result) + " - " + FMOD_ErrorString(result);
				return errorMsg;
			}
		}


		AudioManager::AudioManager()
		{

		}


		AudioManager::~AudioManager()
		{
		}

		void AudioManager::Init()
		{

			CHECKFMODERR(FMOD::System_Create(&GetInstance().m_audiosystem));
			CHECKFMODERR(GetInstance().m_audiosystem->init(MAX_AUDIO_CHANNELS, FMOD_INIT_NORMAL, nullptr));

			// Initialing Channels
			for (int i = 0; i < MAX_AUDIO_CHANNELS; i++)
			{
				// making a shared smart pointers for all the playback channels 
				GetInstance().m_channels.push_back(MakeShared<Channel>());
			}

		}


		void AudioManager::Update()
		{
			if (!GetInstance().m_audiosystem)
			{
				LOG_ERROR("FMOD: No Audio System");
				return;
			}

			CHECKFMODERR(GetInstance().m_audiosystem->update());

		}

		void AudioManager::Shutdown()
		{
			if (!GetInstance().m_audiosystem)
			{
				LOG_ERROR("FMOD: No Audio System");
				return;
			}
			// Closing the system
			CHECKFMODERR(GetInstance().m_audiosystem->close());
			// Finally releaseing the system
			CHECKFMODERR(GetInstance().m_audiosystem->release());
		

		}

		bool AudioManager::LoadSound(const AudioClip& clip, SoundType mode, LoadType type)
		{
			// initial Check t osee if the Sound clip file is already loaded
			if (clip.hasLoaded)
			{
				LOG_WARN("AudioManager: {0} already Loaded", clip.name);
				return false;
			}


			typename SoundList::iterator itr = m_audioClips.find(clip.name);

			// Secondary check to see if the same file is not load from differnt sources
			if (itr != m_audioClips.end())
			{
				LOG_WARN("AudioManager: {0} already Exists", clip.name);
				return false;
			}

			// Creating a new sound pointer to load the sound usingthe Api
			FMOD::Sound* newSound = nullptr;
			
			FMOD_MODE audioMode = ((mode == SoundType::Sound2D) ? (FMOD_DEFAULT) : (FMOD_3D | FMOD_LOOP_NORMAL));

			switch (type)
			{
			case FanshaweGameEngine::Audio::AudioManager::LoadType::SAMPLED:
				
				

				// Create a new sound using FMOD craete
				CHECKFMODERR(m_audiosystem->createSound(clip.filePath.c_str(), audioMode, nullptr, &newSound));


				break;

			case FanshaweGameEngine::Audio::AudioManager::LoadType::STREAMED:

				// Create a new sound using FMOD craete
				CHECKFMODERR(m_audiosystem->createStream(clip.filePath.c_str(), audioMode, nullptr, &newSound));

				break;

			}


			


			// if the new sound is valid, we add it to the cache
			if (!newSound)
			{
				LOG_ERROR("AudioManager: Sound Returned Null {0}", clip.name);
				return false;
			}

			m_audioClips[clip.name] = newSound;

			if (mode == SoundType::Sound3D)
			{
				SetClip3DMinMaxDist(clip, 0.5f, 10.0f);
			}


			// Updating the data in the audio clip to show that the clip ha successfully loaded
			clip.hasLoaded = true;


			LOG_INFO("AudioManager: {0} loaded Successfully", clip.name);

			return true;
		}


		void AudioManager::UnloadSound(const AudioClip& clip)
		{

			typename SoundList::iterator itr = m_audioClips.find(clip.name);

			if (itr == m_audioClips.end())
			{
				// no sound found in the cache with the given name 
				//std::cout << "Audio Manager : " << clip.GetID() << "  : Unload Failed : Sound wasnt loaded " << std::endl;
				return;
			}

			// Release the Bound Sound
			CHECKFMODERR(itr->second->release());

			// Remove the sound from the cache
			m_audioClips.erase(itr);

		}


		int AudioManager::PlaySound(const AudioClip& clip)
		{
			// Iterator for finding the loaded sound from clip list
			typename SoundList::iterator itr = m_audioClips.find(clip.name);

			// If the give nsound is not found 
			if (itr == m_audioClips.end())
			{
				LOG_ERROR("Sound doesnt exist : {0}", clip.name);
				return m_nextChannelId;
			}



			// Setting Looping Bit Flag
			itr->second->setMode(clip.m_shouldLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

			// Get a refence to the channel we are about to use
			SharedPtr<Channel> selectedChannel;

			// Calculte the next Channel Id if needed
			int channelId = m_nextChannelId;

			// Calculte the next Channel Id
			m_nextChannelId = (m_nextChannelId + 1) % MAX_AUDIO_CHANNELS;
			selectedChannel = m_channels[channelId];


			// Set up the playback but pause the sound initially
			//CHECKFMODERR(m_audiosystem->playSound(itr->second, 0, true, &channelRef));
			CHECKFMODERR(GetInstance().m_audiosystem->playSound(itr->second, 0, true, &selectedChannel->fmodCh));


			// Start the play back
			CHECKFMODERR(selectedChannel->fmodCh->setPaused(false));



			return channelId;
		}

		const bool AudioManager::GetChannelPaused(const int id) const
		{
			return false;
		}

		const unsigned int AudioManager::GetSoundCliplength() const
		{
			return 0;
		}
		const float AudioManager::GetChannelVolume(const int id) const
		{
			return 0.0f;
		}
		const float AudioManager::GetChannelPitch(const int id) const
		{
			return 0.0f;
		}
		const float AudioManager::GetChannelPan(const int id) const
		{
			return 0.0f;
		}
		const unsigned int AudioManager::GetPlaybackPosition(const int id) const
		{
			return 0;
		}

		void AudioManager::SetChannelVolume(const float value, const int id)
		{
		}

		void AudioManager::SetChannelPitch(const float value, const int id)
		{

		}
		void AudioManager::SetChannelPan(const float value, const int id)
		{

		}

		void AudioManager::SetClip3DMinMaxDist(const AudioClip& clip, const float min, const float max)
		{
			typename SoundList::iterator itr = m_audioClips.find(clip.name);

			// Secondary check to see if the same file is not load from differnt sources
			if (itr == m_audioClips.end())
			{
				LOG_WARN("AudioManager: {0} Clip doesnt exist", clip.name);
				return;
			}

			m_audioClips[clip.name]->set3DMinMaxDistance(min, max);
		}

		void AudioManager::SetClip3DAttributes(const int channelId, const Vector3& position, const Vector3& velocity)
		{
			FMOD_VECTOR pos = GetFmodVector(position);
			FMOD_VECTOR vel = GetFmodVector(velocity);

			CHECKFMODERR(m_channels[channelId]->fmodCh->set3DAttributes(&pos, &vel));
		}

		void AudioManager::SetListenerAttributes(const Vector3& position, const Vector3& velocity, const Vector3& forward, const Vector3& up)
		{
			FMOD_VECTOR fModPosition = GetFmodVector(position);
			FMOD_VECTOR fModVelocity = GetFmodVector(velocity);
			FMOD_VECTOR fModForward = GetFmodVector(forward);
			FMOD_VECTOR fModUp = GetFmodVector(up);

			CHECKFMODERR(m_audiosystem->set3DListenerAttributes(0, &fModPosition, &fModVelocity, &fModForward, &fModUp));

			//CHECKFMODERR(m_audiosystem->getGeometryOcclusion(&fModPosition, &origin, &direct, &reverb));

		}

		void AudioManager::GetListernerAttributes()
		{

			FMOD_VECTOR fmodPosition;
			FMOD_VECTOR fmodVelocity;
			FMOD_VECTOR fmodForward;
			FMOD_VECTOR fmodUp;

			CHECKFMODERR(GetInstance().m_audiosystem->get3DListenerAttributes(
				0, &fmodPosition, &fmodVelocity, &fmodForward, &fmodUp));
			
			Vector3 position = GetGlmVector(fmodPosition);
			Vector3 forward = GetGlmVector(fmodForward);
			
			//LOG_WARN(" Position {0} : {1} : {2}", position.x, position.y, position.z);
			LOG_WARN(" forward {0} : {1} : {2}", forward.x, forward.y, forward.z);
			
		}

		
	}
}