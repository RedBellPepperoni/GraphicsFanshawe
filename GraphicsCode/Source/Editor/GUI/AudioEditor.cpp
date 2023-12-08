#include "AudioEditor.h"
#include "Editor/Utils/ImGuiUtils.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/Audio/AudioManager.h"
#include "RuntimeEditor.h"


namespace FanshaweGameEngine
{
	using namespace Audio;

	namespace EditorGUI
	{
		

		void DrawEffectEditor(const char* name, bool* isOpen)
		{
			ImGui::Begin(name, isOpen);

			ImGui::SetWindowFontScale(1.8f);
			ImGui::AlignTextToFramePadding();

			ImGui::Text("Day/Night Effect");

			ImGui::Dummy(ImVec2(0.0f, 20.0f));

			float lerp = RuntimeEditor::LightLerp;

		
			ImGui::Text("Night ");
			ImGui::SameLine();
			ImGui::DragFloat("Day", &lerp, 0.005f ,0.00f,1.00f);
			RuntimeEditor::LightLerp = lerp;

			ImGui::Text("Drag the DSlider to Change Night to Day");
			

			ImGui::Dummy(ImVec2(0.0f, 20.0f));

			ImGui::End();


			
		}

	}
}