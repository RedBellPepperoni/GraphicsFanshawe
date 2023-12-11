#pragma once
#include "GameEngine.h"

namespace FanshaweGameEngine 
{

	using namespace Physics;


	class SphereTest
	{
	public:

		SphereTest() = default;
		~SphereTest() = default;

		RigidBody3D& GetRigidBody() const { return *m_body; }
		void SetRigidBody(RigidBody3D* body) { m_body = body; }

	private:


		RigidBody3D* m_body;


	};
}

