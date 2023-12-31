#pragma once
#include "CameraController.h"

namespace FanshaweGameEngine
{

	class FlyCameraController : public CameraController
	{
	public:

		FlyCameraController();
		~FlyCameraController();

		virtual void MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime) override;

		virtual void KeyboardInput(Components::Transform& transform, float deltaTime) override;

		void UpdateCameraView(Components::Transform& transform, float delta);
		

	
	private:

		

		Vector2 m_storedCursorPosition;
		float m_cameraSpeed;

		Vector3 m_positionDelta{};

		float m_PitchDelta = 0.0f;
		float m_YawDelta = 0.0f;
		Vector3 m_PositionDelta {};

	
	};

}

