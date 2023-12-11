#include "XWing.h"
namespace FanshaweGameEngine
{


	void XWing::SetOnCollisionCallback(RigidBody3D* body)
	{


	}


	bool XWing::OnCollision(RigidBody3D* body, Vector3 contactpoint)
	{
		OnShoot();

		return true;
	}

	void XWing::OnShoot()
	{
	}

}