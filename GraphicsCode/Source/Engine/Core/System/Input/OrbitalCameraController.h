#pragma once

#include "CameraController.h"

namespace FanshaweGameEngine
{

	class OrbitalCameraController : public CameraController
	{

		virtual void MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime) override;

		virtual void KeyboardInput(Components::Transform& transform, float deltaTime) override;

		void UpdateCameraView(Components::Transform& transform, float delta);

		virtual void SetFocalPoint(const Vector3& point) override;

	private:

		void MouseRotate(Components::Transform& transform, const Vector2& delta);
		Vector3 CalculatePosition(Components::Transform& transform);



		Vector2 m_storedCursorPosition;
		float m_cameraSpeed;


		float m_PitchDelta = 0.0f;
		float m_YawDelta = 0.0f;
		Vector3 m_PositionDelta{};


		float m_distance = 30.0f;


	};
}

