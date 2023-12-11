#pragma once
#include "GameEngine.h"
namespace FanshaweGameEngine
{
	using namespace Physics;



	class XWing
	{
	public:

		XWing() = default;
		~XWing() = default;

		const bool GetAvailable() const { return !onMission; }
		void SetOnCollisionCallback(RigidBody3D* body);

		RigidBody3D& GetRigidBody() const { return *m_body; }
		void SetRigidBody(RigidBody3D* body) { m_body = body; }


	private:


		bool OnCollision(RigidBody3D* body, Vector3 contactpoint);


		void OnShoot();

	private:

		bool onMission = false;
		RigidBody3D* m_body = nullptr;

	};


}

