#include "FlyCameraController.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/System/Window/Window.h"


namespace FanshaweGameEngine
{
	FlyCameraController::FlyCameraController()
	{
		m_mouseSensitivity = 0.001f;
		m_dampeningFactor = 0.001f;
	}
	FlyCameraController::~FlyCameraController()
	{

	}

	void FlyCameraController::MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime)
	{
		
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
			

			Quaternion rotation = transform.GetRotation();


			Quaternion Pitch = glm::angleAxis(-m_rotationvelocity.y, Vector3(1.0f, 0.0f, 0.0f));
			Quaternion Yaw = glm::angleAxis(-m_rotationvelocity.x, Vector3(0.0f, 1.0f, 0.0f));
			

			rotation = Yaw * rotation;
			rotation = rotation * Pitch;
		
			transform.SetRotation(rotation);
	
			m_previousCurserPos = mousePosition;



		}
		else
		{
			m_rotationvelocity = Vector3(0.0f);
		}


		
		m_rotationvelocity = m_rotationvelocity * pow(m_rotateDampeningFactor, deltaTime);

		UpdateCameraView(transform, deltaTime);
	}

	void FlyCameraController::KeyboardInput(Components::Transform& transform, float deltaTime)
	{
		// Defalut speed
		m_cameraSpeed = 80.0f * deltaTime;

		// Way more if needed
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftShift))
		{
			m_cameraSpeed = 160.0f * deltaTime;
		}

       


		// ============ FORWARD CAMERA MOVEMENT =================

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::W))
        {
            m_velocity += transform.GetForwardVector() * m_cameraSpeed;

			
        }

		// ================ REVERSE CAMERA MOVEMENT =====================

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::S))
        {
            m_velocity -= transform.GetForwardVector() * m_cameraSpeed;
			
        }

		// ================ RIGHT CAMERA MOVEMENT =====================

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::A))
		{
			m_velocity -= transform.GetRightVector() * m_cameraSpeed;
		}

		// ================ LEFT CAMERA MOVEMENT =====================


		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::D))
		{
			m_velocity += transform.GetRightVector () * m_cameraSpeed;
		}

		// ================ UP CAMERA MOVEMENT =====================


		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Space))
		{
			m_velocity += Vector3(0.0f,1.0f,0.0f) * m_cameraSpeed;
		}

		// ================ DOWN CAMERA MOVEMENT =====================
		
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftControl))
		{
			m_velocity -= Vector3(0.0f, 1.0f, 0.0f) * m_cameraSpeed;
		}


       // If there is velocity, move the Object

        if (m_velocity.length() > 0.00001f)
        {
            Vector3 position = transform.GetPosition();
            position += m_velocity * deltaTime;
            transform.SetPosition(position);
            m_velocity = m_velocity * pow(m_dampeningFactor, deltaTime);
        }

		else
		{ 
			m_velocity = Vector3(0.0f);
			
		}

	}

	void FlyCameraController::UpdateCameraView(Components::Transform& transform, float delta)
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

	
	

	
}