#pragma once
#include "GameEngine.h"
#include "Framework/Robot/Robot.h"

using namespace Framework;

class CollisionSystem
{

public:

	 //discreate
	void Update();

	

	void CheckOtherRobotCollisions(Robot& bot, Transform& transform);

	float m_collisionRadius = 2.0f;
};

