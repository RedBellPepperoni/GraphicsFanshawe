#include "XWing.h"
#include "XwingDirector.h"
namespace FanshaweGameEngine
{


	void XWing::SetOnCollisionCallback(RigidBody3D* body)
	{
		body->m_OnCollisionCallback = std::bind(&XWing::OnCollision, this, std::placeholders::_1, std::placeholders::_2);

	}

	void XWing::Update(float deltaTime)
	{

		if (onMission)
		{
			Vector3 Force = Normalize(m_direction) * 1600.0f;

			m_body->SetForce(Force);
			/*Quaternion rot = LookAtRotation(m_direction, Vector3(0.0f, 1.0f, 0.0f));

			m_body->SetRotation(rot);
		}*/
		}

		else
		{
			m_body->SetForce(Vector3(0.0f));
			m_body->SetVelocity(Vector3(0.0f));

		}
	}

	void XWing::FlyMission()
	{ 
		onMission = true;
	}

	void XWing::SetOriginAndTatget(const Vector3& origin, const Vector3& target)
	{
		m_origin = origin;
		m_target = target;

		m_direction = Normalize(m_target -m_origin);
	}


	bool XWing::OnCollision(RigidBody3D* body, Vector3 contactpoint)
	{

		if (body->m_tag == CollisionTag::STARDESTROYER)
		{
			OnShoot();
		}

		

		return true;
	}

	void XWing::OnShoot()
	{
		XwingDirector::GetInstance().ShootMissile(m_body->GetPosition(), m_direction);


		m_direction = -Normalize(m_direction);

		Quaternion rot = LookAtRotation(m_direction, Vector3(0.0f, 1.0f, 0.0f));

		m_body->SetRotation(rot);


		m_body->SetForce(Vector3(0.0f));
		m_body->SetVelocity(Vector3(0.0f));
	}



}