#pragma once
#include <fmod.hpp>
#include <map>
#include <string>
#include <vector>
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/Singleton.h"
#include "Engine/Utils/Math.h"
#include "Engine/Core/ECS/EntityManager.h"


namespace FanshaweGameEngine
{


	namespace Audio
	{

		

		struct AudioGeometry
		{

			FMOD::Geometry* geometry = nullptr;

			Transform* transform = nullptr;

			int polyIndex;

		};


		struct AudioClip
		{

			AudioClip(const std::string& newName,const std::string& newfilePath)
			{
				name = newName;
				filePath = newfilePath;
			}

			// For now the uniqueID is the disk path for the sound
			std::string name = "unknown";

			std::string filePath = "default";

			// Stores if the Sound has been loaded into the Engine
			mutable bool hasLoaded = false;

			// Store if the Sound is OneShot or looping
			bool m_shouldLoop = false;

			// The actual audio data
			FMOD::Sound* audio = nullptr;

		};

		struct Channel
		{
			// the name of the channel
			std::string name = "DefaultChannel";
			// The pointer to the actual fmod channel
			FMOD::Channel* fmodCh = nullptr;

			float volume = 1.0f;

			float pitch = 1.0f;

			float pan = 0.0f;

			bool isPlaying = false;

		};

		static std::string ErrorCheckFMod(FMOD_RESULT result, int line);


#define CHECKFMODERR(fModResult) ErrorCheckFMod(fModResult,__LINE__); 

		


		class AudioManager : public Singleton<AudioManager>
		{

		public:

			enum class LoadType
			{
				SAMPLED,
				STREAMED
			};

			enum class SoundType
			{
				Sound2D,
				Sound3D
			};


			// Type Definitions for readability
			typedef std::map<std::string, FMOD::Sound*> SoundList;
			typedef std::vector<SharedPtr<Channel>> ChannelList;

			// Constructor
			AudioManager();

			//Destructor
			virtual ~AudioManager();

			// Initialized the Core Audio Systems
			static void Init();

			// Called every Frame of the Gameloop
			static void Update();

			// Called to Deactivate/ Shutdown the System after use
			static void Shutdown();


			

			// Sound Loading / Unloading
			bool LoadSound(const AudioClip& clip, SoundType mode = SoundType::Sound2D,LoadType type = LoadType::SAMPLED);


			void UnloadSound(const AudioClip& clip);

			// Sound PlayBack
			int PlaySound(const AudioClip& clip);

			

			// Getter for checking if the current channel is paused
			const bool GetChannelPaused(const int id = 0) const;

			// The Current playing sound's total legnth
			const unsigned int GetSoundCliplength() const;

			const float GetChannelVolume(const int id = 0) const;
			const float GetChannelPitch(const int id = 0) const;
			const float GetChannelPan(const int id = 0) const;

			// The position of the audio playback
			const unsigned int GetPlaybackPosition(const int id = 0) const;

			// Modifying Channel Values
			void SetChannelVolume(const float value, const int id = 0);
			void SetChannelPitch(const float value, const int id = 0);
			void SetChannelPan(const float value, const int id = 0);

			void SetClip3DMinMaxDist(const AudioClip& clip, const float min, const float max);
			void SetClip3DAttributes(const int channelId,const Vector3& position, const Vector3& velocity);

			void SetListenerAttributes(const Vector3& position, const Vector3& velocity, const Vector3& forward, const Vector3& up);


			void AddOcclusionPolygon(AudioGeometry* geo,const Vector2& size, const Vector3& position );


			AudioGeometry* CreateGeometry(Entity& entity);


			void GetListernerAttributes();


		private:
			// The maximum number of Channels for the audio engine 
			static const uint32_t MAX_AUDIO_CHANNELS = 16;


			// pointer to the audiosubsysem from the Fmod api
			static FMOD::System* m_audiosystem;

			int m_nextChannelId = 0;

			// The current seek position (how many miliseconds we are into the playback)
			unsigned int m_CurrentClipLength = 0;



			// The list of all the currently loaded (playable sounds)
			SoundList m_audioClips;

			// Extera storage for channels if multiple audio playback is needed
			// Here the first channel (m_channel[0]) is always reserved for one shot sounds;
			ChannelList m_channels;


			std::vector<AudioGeometry*> m_GeometryList;

		};
	}
}

