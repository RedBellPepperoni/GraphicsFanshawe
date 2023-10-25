#pragma once
#include "Engine/Core/Memory/Memory.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		struct PhysicsProperties;
		class RigidBody3D;
	}


	using Physics::PhysicsProperties;
	using Physics::RigidBody3D;

	namespace Components
	{
		

		class RigidBodyComponent
		{
		public:
			RigidBodyComponent();
			RigidBodyComponent(SharedPtr<RigidBody3D>& otherbody);
			RigidBodyComponent(const PhysicsProperties& properties);

			~RigidBodyComponent();

			SharedPtr<RigidBody3D>& GetRigidBody();

			
			

		private:

			SharedPtr<RigidBody3D> m_rigidBody;
		};

	}
}

