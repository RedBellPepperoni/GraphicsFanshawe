#include "Missile.h"
#include "XwingDirector.h"


namespace FanshaweGameEngine
{

	void Missile::SetOnCollisionCallback(RigidBody3D* body)
	{
		body->m_OnCollisionCallback = std::bind(&Missile::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
	}


	void Missile::FireMissile(const Vector3& direction)
	{


		Direction = Normalize(direction);

		Quaternion rot = LookAtRotation(direction, Vector3(0.0f, 1.0f, 0.0f));
		m_body->SetRotation(rot);

		m_active = true;
	}


	void Missile::Update(float deltaTime)
	{ 
		
		if (!m_active)
		{
			return;
		}


		currentTime += deltaTime;

		if (m_body)
		{
			m_body->SetForce(Direction * 150.0f);
		}



		if (currentTime > timeToLive)
		{
			currentTime = 0.0f;
			m_active = false;
		}

	}

	bool Missile::OnCollision(RigidBody3D* body, Vector3 contactpoint)
	{

		
	   m_active = false;
	   currentTime = 0.0f;
		

		// spawn Explosion

		return true;
	}
}