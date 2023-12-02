#include "RuntimeEditor.h"
#include "ApplicationEditor.h"
#include "AudioEditor.h"
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


			DebugDraw();

			static bool isAppEditorOpen = true;

			
			DrawApplicationEditor("Applicaion Editor", &isAppEditorOpen);
			DrawEffectEditor("Audio Editor", &isAppEditorOpen);
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
