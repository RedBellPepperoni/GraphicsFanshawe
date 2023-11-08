#include "UnitSpawner.h"
#include "GameEngine.h"
#include "Enemy.h"
#include "Human.h"
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

		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);

		transform->SetScale(Vector3(0.02f));
		transform->SetPosition(Vector3(position));
		rigidBody->SetPosition(position);
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
			if (!enforcerMesh)
			{
				LOG_WARN("NO ENFORCER MESH FOUND");
			}
			else
			{
				mesh = enforcerMesh;
			}

			break;
		case Robotron::EnemyType::Hulk:

			if(!hulkMesh)
			{
				LOG_WARN("NO HULK MESH FOUND");
			}
			else
			{
				mesh = hulkMesh;
			}

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

	Human* UnitSpawner::SpawnHuman(HumanType type, const Vector3& position)
	{
		Human* human = nullptr;

		Entity humanEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity("Human");

		PhysicsProperties properties;


		SharedPtr<SphereCollider> collider = MakeShared<SphereCollider>();
		collider->SetRadius(2.0f);

		properties.collider = collider;
		properties.mass = 10.0f;

		properties.tag = CollisionTag::Human;

		// Atatching the Rigidbody to the player entity
		RigidBody3D* rigidBody = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(humanEntity, properties);
		rigidBody->SetPosition(position);

		Transform* transform = &humanEntity.GetComponent<Transform>();

		transform->SetScale(Vector3(0.02f));
		transform->SetPosition(position);
		transform->SetRotation(Vector3(-90.0f, 0.0f, 0.0f));


		SharedPtr<Mesh> mesh = nullptr;

		switch (type)
		{
		case Robotron::HumanType::None:

			LOG_WARN("Trying to spawn a None type Human");

			break;
		case Robotron::HumanType::Daddy:

			if (!daddyMesh)
			{
				LOG_WARN("No Daddy Mesh Found");
			}
			else
			{
				mesh = daddyMesh;
			}

			break;
		case Robotron::HumanType::Mommy:

			if (!mommyMesh)
			{
				LOG_WARN("No Mommy Mesh Found");
			}
			else
			{
				mesh = mommyMesh;
			}

			break;
		case Robotron::HumanType::Mikey:

			if (!mikeyMesh)
			{
				LOG_WARN("No Mikey Mesh Found");
			}
			else
			{
				mesh = mikeyMesh;
			}

			break;
		default:
			break;
		}


		if (mesh)
		{
			humanEntity.AddComponent<MeshComponent>(mesh);
			humanEntity.AddComponent<MeshRenderer>();
		}


		human = &humanEntity.AddComponent<Human>(type, rigidBody);

		human->SetCallBack();


		return human;
	}

	

	void UnitSpawner::SpawnMesh(std::string name, const Vector3 position, const Vector3 scale, const Vector3 rotation)
	{

		Entity MeshEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity("Mesh");




		Transform* transform = &MeshEntity.AddComponent<Transform>();

	

		transform->SetScale(scale);
		transform->SetPosition(Vector3(position));

		transform->SetRotation(rotation);



		SharedPtr<Mesh> mesh = Application::GetCurrent().GetModelLibrary()->GetResource(name)->GetMeshes()[0];

		if (!mesh)
		{
			LOG_WARN("NO  MESH FOUND");

		}
		else
		{
			MeshEntity.AddComponent<MeshComponent>(mesh);
			MeshEntity.AddComponent<MeshRenderer>();
		}
	}



	void UnitSpawner::LoadMeshes()
	{
		SharedPtr<ModelLibrary> modelLib = Application::GetCurrent().GetModelLibrary();

		SharedPtr<Model> model = modelLib->LoadModel("PlayerFront","Assets//PlayerFront.ply");
		playerMesh = model->GetMeshes()[0];


		model = modelLib->LoadModel("Grunt", "Assets//GruntFront.ply");
		gruntMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Hulk", "Assets//HulkFront.ply");
		hulkMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Enforcer", "Assets//Enforcer.ply");
		enforcerMesh = model->GetMeshes()[0];


		model = modelLib->LoadModel("Daddy", "Assets//DaddyFront.ply");
		daddyMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Mommy", "Assets//MommyFront.ply");
		mommyMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Mikey", "Assets//MikeyFront.ply");
		mikeyMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Score1000", "Assets//Score1000.ply");
		model = modelLib->LoadModel("Score2000", "Assets//Score2000.ply");
		model = modelLib->LoadModel("Score3000", "Assets//Score3000.ply");
		model = modelLib->LoadModel("Score4000", "Assets//Score4000.ply");
		model = modelLib->LoadModel("Score5000", "Assets//Score5000.ply");
		model = modelLib->LoadModel("Skull", "Assets//Skull.ply");
		model = modelLib->LoadModel("Arena", "Assets//Arena.ply");
		model = modelLib->LoadModel("Gameover", "Assets//Gameover.ply");
		model = modelLib->LoadModel("GameWin", "Assets//GameWin.ply");
		

	}
}