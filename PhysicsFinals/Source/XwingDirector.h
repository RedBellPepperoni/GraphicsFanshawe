#pragma once
#include "GameEngine.h"


namespace FanshaweGameEngine
{
	using namespace Physics;

	class Missile;

	class XWing;
	class SphereTest;


	class XwingDirector : public Singleton<XwingDirector>
	{


	public:

		void SpawnXWing();

		void SpawnTestSpherePair();

		void TempStartAll();
		
	private:
		
		//Calculates a random origin point
		void CalculateOriginPoint();

		// Calculates a random target point 
		// Optional : force the target point generation so that the xwing will target the Shield genetators
		void CalculateTargetPoint(bool directedtowardsShieldGenerators = false);


		void CalculateXWingPath(XWing* xwing);

		void SpawnWaypointTrails(const Vector2& firstPoint, const Vector2& secondPoint);

		void LaunchXWing(const Vector2& targetPoint);

		bool OnSphereOneCollision(RigidBody3D* body, Vector3 contactpoint);
		bool OnSphereTwoCollision(RigidBody3D* body, Vector3 contactpoint);

	private:


		const int maxXWings = 5;
		//std::vector<Transform*> 

		static int xwingcount;

		std::vector<XWing*> m_XwingList;

		SphereTest* SphereTestOne;
		SphereTest* SphereTestTwo;

		bool finalOriginPoint = false;
		bool finalTargetPoint = false;
	};

}

