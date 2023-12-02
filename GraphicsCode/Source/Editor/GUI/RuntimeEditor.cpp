#include "RuntimeEditor.h"
#include "ApplicationEditor.h"
#include "AudioEditor.h"

#include "Editor/Utils/ImGuiUtils.h"

#include "Engine/Core/Application/Application.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/Rendering/Lights/Light.h"
#include "Engine/Core/Rendering/Renderer/DebugRenderer.h"


namespace FanshaweGameEngine
{
	namespace EditorGUI
	{
		

		RuntimeEditor::RuntimeEditor()
		{
			
		}
		RuntimeEditor::~RuntimeEditor()
		{
		}


		void RuntimeEditor::InitDockingSpace()
		{
			static bool initialized = false;

			// getting the dockspace ID
			ImGuiID dockspaceId = ImGui::DockSpaceOverViewport();

			// get the ref of teh Dock node
			ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockspaceId);

			if (initialized || (dockNode != nullptr))
			{
				// Return if this was already intialized for the node retued null
				return;
			}


			//Otherwise set the Initialized flag 
			initialized = true;

			const float viewportRatio = 0.7f;
			const float editorRatio = 0.15f;
			const float objectListRatio = 0.5f;


			//ImGui::DockBuilderRemoveNode();



		}



		void RuntimeEditor::Toggle(bool isVisible)
		{ 
			m_shouldRender = isVisible;
		}

		

		void RuntimeEditor::OnUpdate()
		{
			if(!m_shouldRender)
			{
				return;
			}

			//NO Docking Yet still need to figure out the ViewportTexture stuff

			//InitDockingSpace();

			DebugDraw();

			static bool isAppEditorOpen = true;

			
			DrawApplicationEditor("Applicaion Editor", &isAppEditorOpen);
			DrawEffectEditor("Audio Editor", &isAppEditorOpen);

			//ImGui::End();
		}


		void RuntimeEditor::DebugDraw()
		{
			ComponentView lightView = Application::GetCurrent().GetCurrentScene()->GetEntityManager()->GetComponentsOfType<Light>();

			int count = 0;

			for (Entity light : lightView)
			{
				const Transform& transform = light.GetComponent<Transform>();
				const Light& lightComp = light.GetComponent<Light>();


				DebugRenderer::DebugDraw(lightComp,transform.GetRotation(),Vector4(1.0f));
				
			}


			std::vector<DebugLineData> lines = DebugRenderer::Get()->GetLines(true);

			

			
		}

		
	}
}
