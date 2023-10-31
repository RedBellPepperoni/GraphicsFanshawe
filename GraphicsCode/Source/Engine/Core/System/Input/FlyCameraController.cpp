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

	void FlyCameraController::MouseInput(Components::Transform* transform, Vector2 mousePosition, float deltaTime)
	{
		
		static bool mouseHeld = false;

		if (Input::InputSystem::GetInstance().GetMouseBtnClicked(Input::MouseButton::Right))
		{
			mouseHeld = true;
			// Makes the Mouse nap to the Screen Edge
			Application::GetCurrent().GetAppWindow()->SetMouseHidden(true);
			m_storedCursorPosition = mousePosition;
			m_previousCurserPos = mousePosition;

			
		}

		if (Input::InputSystem::GetInstance().GetMouseBtnHeld(Input::MouseButton::Right))
		{
			m_rotationvelocity = Vector2((mousePosition.x - m_previousCurserPos.x), (mousePosition.y - m_previousCurserPos.y)) * m_mouseSensitivity * 5.0f;
			
		}
		else
		{
			if (mouseHeld)
			{
				mouseHeld = false;
				// INFINITIE MOUse on x and Y no edge stopping
				Application::GetCurrent().GetAppWindow()->SetMouseHidden(false);
				Application::GetCurrent().GetAppWindow()->SetMousePosition(m_storedCursorPosition);
			}

		}

		Quaternion rotation = transform->GetRotation();
		Quaternion Pitch = glm::angleAxis(-m_rotationvelocity.y, Vector3(1.0f, 0.0f, 0.0f));
		Quaternion Yaw = glm::angleAxis(-m_rotationvelocity.x, Vector3(0.0f, 1.0f, 0.0f));

		rotation = Yaw * rotation;
		rotation = rotation * Pitch;

		transform->SetRotation(rotation);

		m_previousCurserPos = mousePosition;
		m_rotationvelocity = m_rotationvelocity * pow(m_rotateDampeningFactor, deltaTime);
	}

	void FlyCameraController::KeyboardInput(Components::Transform* transform, float deltaTime)
	{
		// Defalut speed
		m_cameraSpeed = 120.0f * deltaTime;

		// Way more if needed
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftShift))
		{
			m_cameraSpeed = 400.0f * deltaTime;
		}

       


		// ============ FORWARD CAMERA MOVEMENT =================

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::W))
        {
            m_velocity += transform->GetForwardVector() * m_cameraSpeed;

			
        }

		// ================ REVERSE CAMERA MOVEMENT =====================

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::S))
        {
            m_velocity -= transform->GetForwardVector() * m_cameraSpeed;
			
        }

		// ================ RIGHT CAMERA MOVEMENT =====================

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::A))
		{
			m_velocity -= transform->GetRightVector() * m_cameraSpeed;
		}

		// ================ LEFT CAMERA MOVEMENT =====================


		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::D))
		{
			m_velocity += transform->GetRightVector () * m_cameraSpeed;
		}

		// ================ UP CAMERA MOVEMENT =====================


		//if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Space))
		//{
		//	m_velocity += Vector3(0.0f,1.0f,0.0f) * m_cameraSpeed;
		//}

		//// ================ DOWN CAMERA MOVEMENT =====================
		//
		//if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftControl))
		//{
		//	m_velocity -= Vector3(0.0f, 1.0f, 0.0f) * m_cameraSpeed;
		//}


       // If there is velocity, move the Object

        if (m_velocity.length() > 0.00001f)
        {
            glm::vec3 position = transform->GetPosition();
            position += m_velocity * deltaTime;
            transform->SetPosition(position);
            m_velocity = m_velocity * pow(m_dampeningFactor, deltaTime);
        }

		else
		{ 
			m_velocity = Vector3(0.0f);
		}

	}

	
	

	
}