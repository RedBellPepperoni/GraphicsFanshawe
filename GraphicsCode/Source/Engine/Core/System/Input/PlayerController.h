#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace Components
	{
		class Transform;
	}
	namespace Physics
	{
		class RigidBody3D;
	}

	using Physics::RigidBody3D;
	using Components::Transform;

	class PlayerController 
	{

	public:

		PlayerController() = default;
		~PlayerController() = default;

		void MouseInput(RigidBody3D& body, Transform& transform, Vector2 mousePosition, float deltaTime);

		void KeyboardInput(RigidBody3D& body, Transform& transform, float deltaTime);

		void UpdateOffsetTransform(RigidBody3D& body, Transform& cameraTransform);

		void SetOffset(const Vector3& newOffset) { m_cameraOffset = newOffset; }

		void SetOnHit(RigidBody3D* body);

		bool OnHit(RigidBody3D*body, Vector3 contactpoint);

	private:

		Vector2 m_storedCursorPosition{0.0f};
		Vector2 m_previousCurserPos{0.0f};
		Vector2 m_rotationvelocity{ 0.0f };
		float m_mouseSensitivity = 0.001f;

		float m_ObjectSpeed = 75.0f;

		Vector3 m_positionDelta{};

		float m_PitchDelta = 0.0f;
		float m_YawDelta = 0.0f;

		Vector3 m_cameraOffset{0.0f};

		


	};


}

