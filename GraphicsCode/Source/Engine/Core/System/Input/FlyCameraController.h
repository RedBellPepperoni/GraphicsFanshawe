#pragma once
#include "CameraController.h"

namespace FanshaweGameEngine
{

	class FlyCameraController : public CameraController
	{
	public:

		FlyCameraController();
		~FlyCameraController();

		virtual void MouseInput(Components::Transform& transform, float xPosition, float yPosition, float deltaTime) override;

		virtual void KeyboardInput(Components::Transform& transform, float deltaTime) override;


	
	private:

		Vector2 m_storedCursorPosition;
		float m_cameraSpeed;

		Vector3 m_positionDelta{};
	};

}

