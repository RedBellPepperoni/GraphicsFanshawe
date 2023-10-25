#include "RigidBodyComponent.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/Resources/ResourceManager.h"

namespace FanshaweGameEngine
{
	namespace Components
	{
		RigidBodyComponent::RigidBodyComponent()
		{
			m_rigidBody = Factory<RigidBody3D>::Create();
		}
		RigidBodyComponent::RigidBodyComponent(SharedPtr<RigidBody3D>& otherbody)
			: m_rigidBody(otherbody)
		{
			
		}
		RigidBodyComponent::RigidBodyComponent(const PhysicsProperties& properties)
		{
			m_rigidBody = Factory<RigidBody3D>::Create(properties);
		}

		RigidBodyComponent::~RigidBodyComponent()
		{
		}

		
		SharedPtr<RigidBody3D>& RigidBodyComponent::GetRigidBody()
		{
			return m_rigidBody;
		}

		
	}
}
