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

		void SetOnCollisionCallback(RigidBody3D* body);

	private:


		bool OnCollision(RigidBody3D* body, Vector3 contactpoint);

		bool m_active = false;

	};


}

