#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <vector>


namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Mesh;
	}
}


using FanshaweGameEngine::Rendering::Mesh;


namespace Robotron
{

	class Bullet;

	class BulletPool
	{
	public:

		BulletPool();
		~BulletPool();

		void Init(int bulletcount);


		Bullet* CreateBullet();


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
