#pragma once
#include "Engine/Core/Audio/AudioSource.h"

namespace FanshaweGameEngine
{
	using namespace Audio;


	namespace EditorGUI
	{

		
			void DrawEffectEditor(const char* name, bool* isOpen = nullptr);


			static bool distortionActive = false;
			static bool reverbActive = false;
			static bool lowPassActive = false;
			static bool highPassActive = false;
			static bool echoActive = false;

			const int RadioChannelId = 0;
			const int FireChannelId = 1;
			
		
	}
}

