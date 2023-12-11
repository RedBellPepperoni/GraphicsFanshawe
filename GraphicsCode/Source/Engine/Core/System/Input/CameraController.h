#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"

namespace FanshaweGameEngine
{
	

	using Rendering::Camera;

	class CameraController
	{
	public:

		CameraController() = default;
		virtual ~CameraController() = default;

		virtual void MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime) {};

		virtual void KeyboardInput(Components::Transform& transform, float deltaTime) {};

		void SetCamera(Camera* camera) { m_camera = camera; }
		Camera* GetCamera() { return m_camera; };

		void SetMouseSensitivity(float newSens) { m_mouseSensitivity = newSens; }


		virtual void SetFocalPoint(const Vector3& point) {}

	protected:

		
		Vector3 m_FocalPoint{0.0f};

		Vector3 m_velocity = Vector3(0.0f);
		Vector2 m_rotationvelocity = Vector2(0.0f);
		float m_cameraSpeed = 0.0f;
		float m_Distance = 0.0f;
		float m_Zoom = 1.0f;

		
		Vector2 m_previousCurserPos = Vector2(0.0f, 0.0f);
		float m_mouseSensitivity = 0.001f;

	
		float m_dampeningFactor = 0.00001f;
		float m_rotateDampeningFactor = 0.00005f;

		Camera* m_camera = nullptr;
	};
}

