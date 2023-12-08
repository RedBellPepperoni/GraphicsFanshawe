#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	class Scene;
	
	


	namespace EditorGUI
	{

		

		class RuntimeEditor
		{



		private:

			bool m_shouldRender = false;
			
			Vector2 m_cachedViewportSize{ 0.0f };
			Vector2 m_cachedViewportPOsition{ 0.0f };



		private:
			void DebugDraw();
			void InitDockingSpace();

		public:

			RuntimeEditor();
			~RuntimeEditor();


			void Toggle(bool isVisible);
			void OnUpdate();

			//void SelectEntity(Entity entity);
			//void UnSelectEntity(Entity entity);

			static float LightLerp;
			
		};
	}
}

