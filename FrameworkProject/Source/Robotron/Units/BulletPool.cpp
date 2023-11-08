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

	void BulletPool::Init(int bulletcount, CollisionTag tag)
	{
		SharedPtr<ModelLibrary> modelLib = Application::GetCurrent().GetModelLibrary();

		SharedPtr<Model> model = modelLib->LoadModel("Bullet", "Assets//SphereBlender.ply");
		SharedPtr<Model> enemyBullet = modelLib->LoadModel("EnforcerBullet", "Assets//EnforcerBullet.ply");

		if (tag == CollisionTag::Playerbullet)
		{
			bulletMesh = model->GetMeshes()[0];
		}
		else if (tag == CollisionTag::Enemybullet)
		{
			bulletMesh = enemyBullet->GetMeshes()[0];
		}

		currentBulletCount = bulletcount;
		
		for (int index = 0; index < currentBulletCount; index++)
		{
			Bullet* spawnedBullet = CreateBullet(tag);
			
		}





	}


	Bullet* BulletPool::CreateBullet(CollisionTag tag)
	{
		namedbulletcount++;

		Bullet* bullet = nullptr;

		std::string name = "Bullet_" + std::to_string(namedbulletcount);

		Entity bulletEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity(name);

		PhysicsProperties properties;

		SharedPtr<SphereCollider> collider = MakeShared<SphereCollider>();
		collider->SetRadius(1.0f);

		properties.collider = collider;
		properties.mass = 50.0f;

		properties.tag = tag;

		// Atatching the Rigidbody to the player entity
		RigidBody3D* rigidBody = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(bulletEntity, properties);
		

		rigidBody->SetPosition(Vector3(50.0f, 0.0f, 50.0f));

		Transform* transform = &bulletEntity.GetComponent<Transform>();

		if (tag == CollisionTag::Playerbullet)
		{
			transform->SetScale(Vector3(0.2f));
		}
		else if (tag == CollisionTag::Enemybullet)
		{
			transform->SetScale(Vector3(0.025f));
			transform->SetRotation(Vector3(-90.0f,0.0f,0.0f));
		}

		

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
		bullet->SetTag(tag);
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

				Bullet* temp = m_activeBullets[size - 1];

				m_activeBullets[size - 1] = m_activeBullets[i];
				m_activeBullets[i] = temp;
				
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
		

		

		if(!m_activeBullets.empty())
		{
			for (Bullet* bullet : m_activeBullets)
			{
				bullet->Update(deltaTime);
			}
		}

		if (!m_availableBullets.empty())
		{
			for (Bullet* bullet : m_availableBullets)
			{
				bullet->Update(deltaTime);
			}
		}

	}
	void BulletPool::RestAll()
	{
		for (Bullet* activeBullet : m_activeBullets)
		{
			m_availableBullets.push_back(activeBullet);
		}

		m_activeBullets.clear();

		for (Bullet* bullet : m_availableBullets)
		{
			bullet->Reset();
		}
	}
}