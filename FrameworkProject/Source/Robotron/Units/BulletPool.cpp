#include "BulletPool.h"
#include "Bullet.h"
#include "GameEngine.h"
#include <string>

using namespace FanshaweGameEngine::Physics;

namespace Robotron
{
	int BulletPool::namedbulletcount = 0;


	BulletPool::BulletPool()
	{
	}


	BulletPool::~BulletPool()
	{
	}

	void BulletPool::Init(int bulletcount)
	{
		SharedPtr<ModelLibrary> modelLib = Application::GetCurrent().GetModelLibrary();

		SharedPtr<Model> model = modelLib->LoadModel("Bullet", "Assets//SphereBlender.ply");

		bulletMesh = model->GetMeshes()[0];

		currentBulletCount = bulletcount;
		
		for (int index = 0; index < currentBulletCount; index++)
		{
			Bullet* spawnedBullet = CreateBullet();
			
		}





	}


	Bullet* BulletPool::CreateBullet()
	{

		Bullet* bullet = nullptr;

		std::string name = "Bullet_" + std::to_string(namedbulletcount);

		Entity bulletEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity(name);

		PhysicsProperties properties;

		SharedPtr<SphereCollider> collider = MakeShared<SphereCollider>();
		collider->SetRadius(1.0f);

		properties.collider = collider;
		properties.mass = 50.0f;

		properties.tag = CollisionTag::Playerbullet;

		// Atatching the Rigidbody to the player entity
		RigidBody3D* rigidBody = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(bulletEntity, properties);
		//rigidBody->SetPosition(Vector3(1000.0f, 0.0f, 1000.0f));
		rigidBody->SetPosition(Vector3(50.0f, 0.0f, 50.0f));

		Transform* transform = &bulletEntity.GetComponent<Transform>();

		transform->SetScale(Vector3(0.2f));
		transform->SetPosition(Vector3(50.0f, 0.0f, 50.0f));
		





		if (!bulletMesh)
		{
			LOG_WARN("NO BULLET MESH FOUND");

		}
		else
		{
			bulletEntity.AddComponent<MeshComponent>(bulletMesh);
			bulletEntity.AddComponent<MeshRenderer>();
		}




		bullet = &bulletEntity.AddComponent<Bullet>(rigidBody);

		bullet->SetParentPool(this);
		bullet->SetCallBack();

		// Add to avaibale list
		m_availableBullets.push_back(bullet);

		return bullet;
	}

	void BulletPool::PushToAvailable(Bullet* bullet)
	{
		 size_t size= m_activeBullets.size();

		 

		for (int i = 0; i < size; i++)
		{
			if (m_activeBullets[i] == bullet)
			{
				//swappign the current bullet with the last index
				m_activeBullets[size - 1] = m_activeBullets[i];
				
				// Storing the bullet in avaibale pool
				m_availableBullets.push_back(m_activeBullets.back());

				//removing teh bullet from the active pool
				m_activeBullets.pop_back();
				return;
			}
			
		}
	}

	Bullet* BulletPool::PushToActive()
	{

		if(m_availableBullets.empty())
		{
			LOG_WARN("No bullets available");
			return nullptr;
		}

		Bullet* bulletToShoot = m_availableBullets.back();

		// Getting the last index from available bullets
		m_activeBullets.push_back(bulletToShoot);

		// Removing the bullet from the available list
		m_availableBullets.pop_back();


		return bulletToShoot;

	}


	void BulletPool::Update(float deltaTime)
	{
		for (Bullet* bullet : m_activeBullets)
		{
			bullet->Update(deltaTime);
		}

		for (Bullet* bullet : m_availableBullets)
		{
			bullet->Update(deltaTime);
		}

		if(!m_activeBullets.empty())
		{
			
		}

		if (!m_availableBullets.empty())
		{
			
		}

	}
}