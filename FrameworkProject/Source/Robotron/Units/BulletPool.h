#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <stdint.h>
#include <vector>


namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Mesh;
	}

	namespace Physics
	{
		enum CollisionTag;
	}
}


using FanshaweGameEngine::Rendering::Mesh;
using FanshaweGameEngine::Physics::CollisionTag;


namespace Robotron
{

	class Bullet;
	

	class BulletPool
	{
	public:

		BulletPool();
		~BulletPool();

		void Init(int bulletcount, CollisionTag tag);


		Bullet* CreateBullet(CollisionTag tag);


		void PushToAvailable(Bullet* bullet);
		
		Bullet* PushToActive();

		void Update(float deltaTime);


	protected:
	
		std::vector<Bullet*> m_availableBullets{};
		std::vector<Bullet*> m_activeBullets{};

		int currentBulletCount = 0;

		static int namedbulletcount;

		SharedPtr<Mesh> bulletMesh = nullptr;
	};

}
