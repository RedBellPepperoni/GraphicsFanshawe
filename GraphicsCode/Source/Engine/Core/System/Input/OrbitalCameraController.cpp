#include "OrbitalCameraController.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/System/Window/Window.h"


namespace FanshaweGameEngine
{
	void OrbitalCameraController::MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime)
	{
		m_distance = Distance(transform.GetPosition(), m_FocalPoint);


		static bool mouseHeld = false;

		if (Input::InputSystem::GetInstance().GetMouseBtnClicked(Input::MouseButton::Right))
		{
			mouseHeld = true;
			Application::GetCurrent().GetAppWindow().SetMouseHidden(true);

			m_storedCursorPosition = mousePosition;
			m_previousCurserPos = m_storedCursorPosition;



		}

		if (Input::InputSystem::GetInstance().GetMouseBtnHeld(Input::MouseButton::Right))
		{
			m_mouseSensitivity = 0.0002f;
			m_rotationvelocity = Vector2((mousePosition.x - m_previousCurserPos.x), (mousePosition.y - m_previousCurserPos.y)) * m_mouseSensitivity * 10.0f;

		}
		else
		{
			if (mouseHeld)
			{
				mouseHeld = false;
				// INFINITIE MOUse on x and Y no edge stopping
				Application::GetCurrent().GetAppWindow().SetMouseHidden(false);
				Application::GetCurrent().GetAppWindow().SetMousePosition(m_storedCursorPosition);
			}

		}

		if (Length(m_rotationvelocity) > 0.0001f || m_PitchDelta > 0.0001f || m_YawDelta > 0.0001f)
		{
			MouseRotate(transform, m_rotationvelocity);
			m_previousCurserPos = mousePosition;

			Quaternion rotation = transform.GetRotation();


			Quaternion Pitch = glm::angleAxis(-m_PitchDelta, Vector3(1.0f, 0.0f, 0.0f));
			Quaternion Yaw = glm::angleAxis(-m_YawDelta, Vector3(0.0f, 1.0f, 0.0f));


			rotation = Yaw * rotation;
			rotation = rotation * Pitch;

			transform.SetRotation(rotation);

			//m_previousCurserPos = mousePosition;



		}
		else
		{
			m_rotationvelocity = Vector3(0.0f);
		}



		m_rotationvelocity = m_rotationvelocity * pow(m_rotateDampeningFactor, deltaTime);




		UpdateCameraView(transform, deltaTime);


		transform.SetPosition(CalculatePosition(transform));
	}



	void OrbitalCameraController::KeyboardInput(Components::Transform& transform, float deltaTime)
	{
	}
	void OrbitalCameraController::UpdateCameraView(Components::Transform& transform, float delta)
	{

		const float YawSign = transform.GetUpVector().y < 0 ? -1.0f : 1.0f;

		// Extra step to handle the problem when the camera direction is the same as the up vector
		const float cosAngle = glm::dot(transform.GetForwardVector(), transform.GetUpVector());
		if (cosAngle * YawSign > 0.99f)
			m_PitchDelta = 0.f;

		// damping for smooth camera
		m_YawDelta *= pow(m_dampeningFactor, delta);
		m_PitchDelta *= pow(m_dampeningFactor, delta);
		m_PositionDelta *= pow(m_dampeningFactor, delta);
	}


	void OrbitalCameraController::MouseRotate(Components::Transform& transform, const Vector2& delta)
	{
		const float yawSign = transform.GetUpVector().y < 0.0f ? -1.0f : 1.0f;
		m_YawDelta += yawSign * delta.x * 0.3f;
		m_PitchDelta += delta.y * 0.3f;
	}
	Vector3 OrbitalCameraController::CalculatePosition(Components::Transform& transform)
	{
		return m_FocalPoint + transform.GetForwardVector() * m_distance + m_PositionDelta;
	}
}