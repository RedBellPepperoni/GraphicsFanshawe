#include "RuntimeEditor.h"
#include "ApplicationEditor.h"
#include "AudioEditor.h"


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

			static bool isAppEditorOpen = true;

			
			DrawApplicationEditor("Applicaion Editor", &isAppEditorOpen);
			DrawEffectEditor("Audio Editor", &isAppEditorOpen);
		}
	}
}
