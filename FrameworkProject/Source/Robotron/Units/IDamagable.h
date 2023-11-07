#pragma once

namespace Robotron
{


	class IDamagable
	{
	public:

		IDamagable() {};
		virtual ~IDamagable() {};

		virtual void TakeDamage(const int damage) = 0;

	protected:

		int m_health = 100;
		int m_maxHealth = 100;


	};

}