#include "ApplicationEditor.h"
#include "Editor/Utils/ImGuiUtils.h"
#include "Engine/Core/Application/Application.h"

namespace FanshaweGameEngine
{
	namespace EditorGUI
	{
		void DrawApplicationEditor(const char* name, bool* isOpen)
		{
			Application& app = Application::GetCurrent();

			ImGui::Begin(name, isOpen);
			ImGui::AlignTextToFramePadding();

			ImGui::Text("current FPS: %d | total elapsed time: %f seconds", (int)Time::GetFPS(), Time::CurrentTime());
			ImGui::Text("time delta: %fms | frame interval: %fms", Time::DeltaTime() * 1000.0f, Time::UnscaledDeltaTime() * 1000.0f);

			ImGui::End();
		}
	}
}