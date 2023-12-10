#include "PlayerController.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Input/InputSystem.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/System/Window/Window.h"

namespace FanshaweGameEngine
{
	


	void PlayerController::MouseInput(RigidBody3D& body, Transform& transform, Vector2 mousePosition, float deltaTime)
	{

		if(playerDead)
		{
			return;
		}

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


			Quaternion rotation = body.GetRotation();
			

			Quaternion Pitch = glm::angleAxis(-m_rotationvelocity.y, Vector3(1.0f, 0.0f, 0.0f));
			Quaternion Yaw = glm::angleAxis(-m_rotationvelocity.x, Vector3(0.0f, 1.0f, 0.0f));
			//LOG_CRITICAL("{0} : {1} : {2} : {3}", rotation.x, rotation.y, rotation.z, rotation.w);
			//LOG_CRITICAL("{0} : {1} : {2} : {3}", Pitch.x, Pitch.y, Pitch.z, Pitch.w);

			rotation = Yaw * rotation;
			rotation = rotation * Pitch;
			body.SetRotation(rotation);

			
		

			m_previousCurserPos = mousePosition;



		}
		else
		{
			m_rotationvelocity = Vector3(0.0f);
		}



		m_rotationvelocity = m_rotationvelocity * pow(0.0001f, deltaTime);

		//Vector3 bodyUpVector = body.GetRotation() * Vector3(0.0f, 1.0f, 0.0f);
		//Vector3 bodyFrowardVector = body.GetRotation() * Vector3(0.0f, 0.0f, -1.0f);
		//const float YawSign = bodyUpVector.y < 0 ? -1.0f : 1.0f;

		//// Extra step to handle the problem when the camera direction is the same as the up vector
		//const float cosAngle = glm::dot(bodyFrowardVector, bodyUpVector);
		//if (cosAngle * YawSign > 0.99f)
		//	m_PitchDelta = 0.f;

		//// damping for smooth camera
		//m_YawDelta *= pow(0.001f, deltaTime);
		//m_PitchDelta *= pow(0.001f, deltaTime);
		//m_PositionDelta *= pow(0.001f, delta);


	}


	void PlayerController::KeyboardInput(RigidBody3D& body, Transform& transform, float deltaTime)
	{
		if (playerDead)
		{
			body.SetVelocity(Vector3(0.0f));

			if (crackTransform)
			{

				Vector3 forward = Normalize(transform.GetForwardVector());

				crackTransform->SetPosition(transform.GetPosition() + forward * 1.3f);

				Quaternion rotation = LookAtRotation(forward, Vector3(0.0f, 1.0f, 0.0f));

				crackTransform->SetRotation(rotation);
			}

			return;
		}

		body.SetForce(Vector3(0.0f));

		float tempObjectSpeed = m_ObjectSpeed;

		// Way more if needed
		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftShift))
		{
			tempObjectSpeed = m_ObjectSpeed * 3.0f;
		}
		




		// ============ FORWARD CAMERA MOVEMENT =================

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::W))
		{
			body.SetForce(transform.GetForwardVector() * tempObjectSpeed);

		}

		// ================ REVERSE CAMERA MOVEMENT =====================

		else if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::S))
		{
			body.SetForce(transform.GetForwardVector() * -tempObjectSpeed);

		}

		

		// ================ RIGHT CAMERA MOVEMENT =====================

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::A))
		{
			body.SetForce(transform.GetRightVector() * -tempObjectSpeed);
		}

		// ================ LEFT CAMERA MOVEMENT =====================


		else if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::D)) 
		{
			body.SetForce(transform.GetRightVector() * tempObjectSpeed);
		}

		

		// ================ UP CAMERA MOVEMENT =====================


		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Space))
		{
			body.SetForce(Vector3(0.0f,1.0f,0.0f) * tempObjectSpeed);
		}

		// ================ DOWN CAMERA MOVEMENT =====================

		if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::LeftControl))
		{
			body.SetForce(Vector3(0.0f, -1.0f, 0.0f) * tempObjectSpeed);
		}

		



	}


	void PlayerController::UpdateOffsetTransform(RigidBody3D& body, Transform& cameraTransform)
	{
		Quaternion finalRotation = body.GetRotation();
		Vector3 forwardDir = Normalize(finalRotation * Vector3(0.0f, 0.0f, -1.0f));
		Vector3 upDir = Normalize(finalRotation * Vector3(0.0f, 1.0f,0.0f ));
	

		Vector3 finalPosition = body.GetPosition() +  (forwardDir * m_cameraOffset.z) + (upDir * m_cameraOffset.y);

		
		Quaternion cameraRot = LookAtRotation(forwardDir, Vector3(0.0f, 1.0f, 0.0f));
		
		
		//finalMatrix = body.GetTransform() * finalMatrix;
		cameraTransform.SetPosition(finalPosition);
		cameraTransform.SetRotation(cameraRot);


		

		//LOG_CRITICAL("{0} : {1} : {2} : {3}", finalRotation.x, finalRotation.y, finalRotation.z, finalRotation.w);
	}


	void PlayerController::SetOnHit(RigidBody3D* body)
	{
		body->m_OnCollisionCallback = std::bind(&PlayerController::OnHit, this, std::placeholders::_1, std::placeholders::_2);
	}

	bool PlayerController::OnHit(RigidBody3D* body,Vector3 contactpoint)
	{
		if (playerDead)
		{
			return false;
		}

		LOG_CRITICAL("HIT at {0} : {1} : {2}",contactpoint.x,contactpoint.y,contactpoint.z);
		


		playerDead = true;

		return true;
	}

	void PlayerController::SetCrackReference(Transform* transform)
	{
		crackTransform = transform;
	}
	void PlayerController::Reset()
	{
		playerDead = false;
		crackTransform->SetPosition(Vector3(10000.0f));
	}
}
