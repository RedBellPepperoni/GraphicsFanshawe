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

		Quaternion rot = LookAtRotation(Direction, Vector3(0.0f, 1.0f, 0.0f));
		m_body->SetRotation(rot);

		currentTime = 0.0f;

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
			Vector3 pos = m_body->GetPosition();
			m_body->SetForce(Direction * 150.0f);
			Quaternion rot = LookAtRotation(Direction, Vector3(0.0f, 1.0f, 0.0f));
			m_body->SetRotation(rot);

			//LOG_WARN("{0}: {1} : {2}", pos.x, pos.y, pos.z);
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

	   m_body->SetPosition(Vector3(-1000.0f));
	   currentTime = 0.0f;

		return true;
	}
}