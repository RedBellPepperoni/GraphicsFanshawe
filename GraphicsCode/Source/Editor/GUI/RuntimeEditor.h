#pragma once

namespace FanshaweGameEngine
{
	namespace EditorGUI
	{
		class RuntimeEditor
		{

		private:

			bool m_shouldRender = false;


		public:

			RuntimeEditor();
			~RuntimeEditor();


			void Toggle(bool isVisible);
			void OnUpdate();
		};
	}
}

