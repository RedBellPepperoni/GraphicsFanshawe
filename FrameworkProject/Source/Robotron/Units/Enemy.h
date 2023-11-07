#pragma once
#include "BaseUnit.h"
#include "UnitManager.h"


namespace Robotron
{
	enum class EnemyType : uint8_t
	{
		Grunt,
		Spheroid,
		Enforcer,
		Hulk
	};



	class Enemy : public BaseUnit
	{
	public:
		Enemy(const EnemyType type, RigidBody3D* body);
		~Enemy() {};

		void Update(float deltaTime) override;

	private:


		EnemyType m_type;


	};
}

