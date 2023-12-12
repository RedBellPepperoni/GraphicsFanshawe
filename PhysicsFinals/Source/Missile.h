#pragma once
#include "GameEngine.h"


namespace FanshaweGameEngine
{
	using namespace Physics;



	class Missile
	{
	public:
		Missile() = default;
		~Missile() = default;

		bool GetActive() { return m_active; }
		void SetPosition(const Vector3& position) { m_body->SetPosition(position); }

		void SetOnCollisionCallback(RigidBody3D* body);

		void SetRigidBodyRef(RigidBody3D* body)
		{
			m_body = body;
		}

		void FireMissile(const Vector3& direction);

		void Update(float deltaTime);

	private:


		bool OnCollision(RigidBody3D* body, Vector3 contactpoint);

		float currentTime = 0.0f;
		Vector3 Direction{ 0.0f,1.0f,0.0f };
	
		const float timeToLive = 4.0f;

		bool m_active = false;

		RigidBody3D* m_body = nullptr;

	};


}

