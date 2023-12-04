#include "AudioEditor.h"
#include "Editor/Utils/ImGuiUtils.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/Audio/AudioManager.h"



namespace FanshaweGameEngine
{
	using namespace Audio;

	namespace EditorGUI
	{
		

		void DrawEffectEditor(const char* name, bool* isOpen)
		{
			ImGui::Begin(name, isOpen);

			//ImGui::SetWindowFontScale(1.8f);
			//ImGui::AlignTextToFramePadding();

			//ImGui::Text("Audio DSP Effects");

			//ImGui::Dummy(ImVec2(0.0f, 20.0f));

			//float volume = AudioManager::GetInstance().GetChannelVolume(RadioChannelId);

			//ImGui::DragFloat("Radio Volume", &volume, 0.01f ,0.00f,4.0f);

			//AudioManager::GetInstance().SetChannelVolume(volume);


			//ImGui::Dummy(ImVec2(0.0f, 20.0f));

			//if (ImGui::Button(distortionActive ? "Disable Distortion" : "Enable Distortion"))
			//{
			//	distortionActive = !distortionActive;
			//	AudioManager::GetInstance().SetDSPState(0,DSPEffects::DISTORTION, distortionActive);

			//}
			//
			//
			//if (ImGui::Button(reverbActive ? "Disable Reverb" : "Enable Reverb"))
			//{
			//	reverbActive = !reverbActive;
			//	AudioManager::GetInstance().SetDSPState(0,DSPEffects::REVERB, reverbActive);

			//}

			//
			//if (ImGui::Button(lowPassActive ? "Disable LowPass" : "Enable LowPass"))
			//{
			//	lowPassActive = !lowPassActive;
			//	AudioManager::GetInstance().SetDSPState(0, DSPEffects::LOWPASS, lowPassActive);

			//}

			//if (ImGui::Button(highPassActive ? "Disable HighPass" : "Enable HighPass"))
			//{
			//	highPassActive = !highPassActive;
			//	AudioManager::GetInstance().SetDSPState(0, DSPEffects::HIGHPASS, highPassActive);

			//}
			//
			//if (ImGui::Button(echoActive ? "Disable ECHO" : "Enable ECHO"))
			//{
			//	echoActive = !echoActive;
			//	AudioManager::GetInstance().SetDSPState(0, DSPEffects::ECHO, echoActive);

			//}

			//


			ImGui::End();
		}

	}
}