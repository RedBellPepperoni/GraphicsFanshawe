#include "UnitSpawner.h"
#include "GameEngine.h"
#include "Enemy.h"
#include "Player.h"


using namespace FanshaweGameEngine::Physics;

namespace Robotron
{
	UnitSpawner::UnitSpawner()
	{
	}
	UnitSpawner::~UnitSpawner()
	{
	}


	Player* UnitSpawner::SpawnPlayer()
	{
		Player* player = nullptr;

		Entity playerEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity("Player");

		PhysicsProperties properties;

		SharedPtr<SphereCollider> collider = MakeShared<SphereCollider>();
		collider->SetRadius(2.0f);

		

		properties.collider = collider;
		properties.mass = 10.0f;

		ColliderType type = properties.collider->GetType();

		properties.tag = CollisionTag::Player;

		// Atatching the Rigidbody to the player entity
		RigidBody3D* rigidBody = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(playerEntity, properties);


		Transform* transform = &playerEntity.GetComponent<Transform>();

		transform->SetScale(Vector3(0.02f));

		transform->SetRotation(Vector3(-90.0f,0.0f,0.0f));


		


		if (!playerMesh)
		{
			LOG_WARN("NO PLAYER MESH FOUND");
			
		}
		else
		{
			playerEntity.AddComponent<MeshComponent>(playerMesh);
			playerEntity.AddComponent<MeshRenderer>();
		}
	



		player = &playerEntity.AddComponent<Player>(rigidBody);

		player->SetCallBack();





		return player;
	}


	Enemy* UnitSpawner::SpawnEnemy(EnemyType type, const Vector3& position)
	{
		Enemy* enemy = nullptr;

		Entity enemyEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity("Enemy");

		PhysicsProperties properties;


		SharedPtr<SphereCollider> collider = MakeShared<SphereCollider>();
		collider->SetRadius(2.0f);

		properties.collider = collider;
		properties.mass = 10.0f;
		
		properties.tag = CollisionTag::Enemy;

		// Atatching the Rigidbody to the player entity
		RigidBody3D* rigidBody = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(enemyEntity, properties);
		rigidBody->SetPosition(position);

		Transform* transform = &enemyEntity.GetComponent<Transform>();

		transform->SetScale(Vector3(0.02f));
		transform->SetPosition(position);
		transform->SetRotation(Vector3(-90.0f, 0.0f, 0.0f));


		SharedPtr<Mesh> mesh = nullptr;

		switch (type)
		{
		case Robotron::EnemyType::Grunt:

			if (!gruntMesh)
			{
				LOG_WARN("NO GRUNT MESH FOUND");
			}
			else
			{
				mesh = gruntMesh;
			}


			break;
		case Robotron::EnemyType::Spheroid:


			break;
		case Robotron::EnemyType::Enforcer:


			break;
		case Robotron::EnemyType::Hulk:


			break;
		default:
			break;
		}


		if (mesh)
		{
			enemyEntity.AddComponent<MeshComponent>(mesh);
			enemyEntity.AddComponent<MeshRenderer>();
		}


		enemy = &enemyEntity.AddComponent<Enemy>(type,rigidBody);

		enemy->SetCallBack();

		
		return enemy;
	}


	void UnitSpawner::LoadMeshes()
	{
		SharedPtr<ModelLibrary> modelLib = Application::GetCurrent().GetModelLibrary();

		SharedPtr<Model> model = modelLib->LoadModel("PlayerFront","Assets//PlayerFront.ply");

		playerMesh = model->GetMeshes()[0];


		model = modelLib->LoadModel("Grunt", "Assets//GruntFront.ply");

		gruntMesh = model->GetMeshes()[0];

	}
}