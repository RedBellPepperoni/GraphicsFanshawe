#include "Missile.h"
#include "Source/XwingDirector.h"


namespace FanshaweGameEngine
{

	void Missile::SetOnCollisionCallback(RigidBody3D* body)
	{
		// Set the collision callback
		body->m_OnCollisionCallback = std::bind(&Missile::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
	}

	bool Missile::OnCollision(RigidBody3D* body, Vector3 contactpoint)
	{
		// spawn Explosion

		return true;
	}
}