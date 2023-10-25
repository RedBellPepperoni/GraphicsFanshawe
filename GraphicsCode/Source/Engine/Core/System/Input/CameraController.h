#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/ECS/Components/Transform.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Camera;
	}


	using Rendering::Camera;

	class CameraController
	{
	public:

		CameraController() = default;
		virtual ~CameraController() = default;

		virtual void MouseInput(Components::Transform& transform, float xPosition, float yPosition, float deltaTime) {};

		virtual void KeyboardInput(Components::Transform& transform, float deltaTime) {};

		void SetCamera(Camera* camera) { m_camera = camera; }

		void SetMouseSensitivity(float newSens) { m_mouseSensitivity = newSens; }

	protected:

	protected:

		
		Vector3 m_FocalPoint;

		Vector3 m_velocity;
		float m_cameraSpeed = 0.0f;
		float m_Distance = 0.0f;
		float m_Zoom = 1.0f;

		
		Vector2 m_previousCurserPos = Vector2(0.0f, 0.0f);
		float m_mouseSensitivity = 0.1f;

	
		float m_dampeningFactor = 0.00001f;
		float m_rotateDampeningFactor = 0.001f;

		Camera* m_camera = nullptr;
	};
}

