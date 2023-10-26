#include "FlyCameraController.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	FlyCameraController::FlyCameraController()
	{
		m_mouseSensitivity = 0.001f;
		m_dampeningFactor = 0.005f;
	}
	FlyCameraController::~FlyCameraController()
	{

	}
	void FlyCameraController::MouseInput(Components::Transform& transform, Vector2 mousePosition, float deltaTime)
	{
		// center to the top left
		Vector2 center = Vector2(0.0f);


		Application::GetCurrent().SetCursorPosition(center);


		m_rotationvelocity = Vector2((mousePosition.x - m_previousCurserPos.x), (mousePosition.y - m_previousCurserPos.y)) * m_mouseSensitivity * 5.0f;

		Quaternion rotation = transform.GetRotation();
		Quaternion rotX = glm::angleAxis(-m_rotationvelocity.y, Vector3(1.0f, 0.0f, 0.0f));
		Quaternion rotY = glm::angleAxis(m_rotationvelocity.x, Vector3(0.0f, 1.0f, 0.0f));

		rotation = rotY * rotation;
		rotation = rotation * rotX;


		transform.SetRotation(rotation);

		m_previousCurserPos = mousePosition; 

		m_rotationvelocity = m_rotationvelocity * pow(m_rotateDampeningFactor, deltaTime);

	}

	void FlyCameraController::KeyboardInput(Components::Transform& transform, float deltaTime)
	{

        m_cameraSpeed = 1000.0f * deltaTime;


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
			m_velocity += transform.GetUpVector() * m_cameraSpeed;
		}

		// ================ DOWN CAMERA MOVEMENT =====================
		
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftControl))
		{
			m_velocity -= transform.GetUpVector() * m_cameraSpeed;
		}


       // If there is velocity, move the Object

        if (m_velocity.length() > 0.00001f)
        {
            glm::vec3 position = transform.GetPosition();
            position += m_velocity * deltaTime;
            transform.SetPosition(position);
            m_velocity = m_velocity * pow(m_dampeningFactor, deltaTime);
        }

		else
		{ 
			m_velocity = Vector3(0.0f);
		}

	}

	
	

	
}