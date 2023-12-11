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

		void Update(float deltaTime);

		void FlyMission();
		
		void SetOriginAndTatget(const Vector3& origin, const Vector3& target);

	private:


		bool OnCollision(RigidBody3D* body, Vector3 contactpoint);


		void OnShoot();

	private:

		bool onMission = false;

		

		RigidBody3D* m_body = nullptr;

		Vector3 m_direction = Vector3(0.0f, 0.0f, 1.0f);

		Vector3 m_origin = Vector3(0.0f);
		Vector3 m_target = Vector3(0.0f);



	};


}

