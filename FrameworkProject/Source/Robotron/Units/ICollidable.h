#pragma once


namespace FanshaweGameEngine
{
	namespace Physics
	{
		class RigidBody3D;
	}
}

using FanshaweGameEngine::Physics::RigidBody3D;

namespace Robotron
{


	class ICollidable
	{
	public:

		ICollidable() {};
		virtual ~ICollidable() {};

		virtual bool OnCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo) = 0;

	protected:

		



	};

}