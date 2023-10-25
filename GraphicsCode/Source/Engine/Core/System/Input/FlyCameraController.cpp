#include "FlyCameraController.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Input/InputSystem.h"

namespace FanshaweGameEngine
{
	FlyCameraController::FlyCameraController()
	{

	}
	FlyCameraController::~FlyCameraController()
	{

	}
	void FlyCameraController::MouseInput(Components::Transform& transform, float xPosition, float yPosition, float deltaTime)
	{
		Vector2 center = Vector2(0.0f);
		Application::GetCurrent().SetCursorPosition(center);


		xPosition -= center.x;
		yPosition -= center.y;

		

		Vector3 eularAngles = transform.GetEulerRotation();
		float pitch = eularAngles.x;
		float yaw = eularAngles.y;

		pitch -= (yPosition)*m_mouseSensitivity;
		yaw -= (xPosition)*m_mouseSensitivity;


		transform.SetRotation(Quaternion(Vector3(pitch, yaw, eularAngles.z)));

		m_previousCurserPos = Vector2(xPosition, yPosition);

	}

	void FlyCameraController::KeyboardInput(Components::Transform& transform, float deltaTime)
	{

        m_cameraSpeed = 1000.0f * deltaTime;

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::W))
        {
            m_velocity += transform.GetForwardVector() * m_cameraSpeed;
        }

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::S))
        {
            m_velocity -= transform.GetForwardVector() * m_cameraSpeed;
        }

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::A))
		{
			m_velocity -= transform.GetRightVector() * m_cameraSpeed;
		}

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::D))
		{
			m_velocity += transform.GetForwardVector() * m_cameraSpeed;
		}

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Space))
		{
			m_velocity += transform.GetUpVector() * m_cameraSpeed;
		}
		
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftControl))
		{
			m_velocity -= transform.GetUpVector() * m_cameraSpeed;
		}


       

        if (m_velocity.length() > 0.00001f)
        {
            glm::vec3 position = transform.GetPosition();
            position += m_velocity * deltaTime;
            transform.SetPosition(position);
            m_velocity = m_velocity * pow(m_dampeningFactor, deltaTime);
        }

	}
	

	
}