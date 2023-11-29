#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace EditorGUI
	{
		class RuntimeEditor
		{

		private:

			bool m_shouldRender = false;

			enum EditorDebugFlags : uint32_t 
			{
				Grid = 1,
				Gizmo = 2,
				ViewSelected = 4,
				CameraFrustum = 8,
				MeshBoundingBoxes = 16,
				SpriteBoxes = 32,
				EntityNames = 64,

			};


		public:

			RuntimeEditor();
			~RuntimeEditor();


			void Toggle(bool isVisible);
			void OnUpdate();
		};
	}
}

