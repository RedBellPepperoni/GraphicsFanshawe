#include "UnitSpawner.h"
#include "GameEngine.h"
#include "Enemy.h"
#include "Human.h"
#include "Player.h"
#include "Robotron/Animation/Animator.h"

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


		MeshComponent* comp = nullptr;


		if (!playerMesh)
		{
			LOG_WARN("NO PLAYER MESH FOUND");
			
		}
		else
		{
			comp = &playerEntity.AddComponent<MeshComponent>(playerMesh);
			playerEntity.AddComponent<MeshRenderer>();
		}
	



		player = &playerEntity.AddComponent<Player>(rigidBody);

		player->SetCallBack();

		Animator* animator = &playerEntity.AddComponent<Animator>();

		animator->SetMeshComponentRef(comp);

		player->SetAnimtor(animator);

		float playback = 0.2f;

		AnimationClip frontwalkclip;
	
		frontwalkclip.playback = playback;
		frontwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerFront01")->GetMeshes()[0]);
		frontwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerFront")->GetMeshes()[0]);
		frontwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerFront02")->GetMeshes()[0]);

		animator->AddAnimationClip("WalkFront", frontwalkclip);

		AnimationClip backwalkclip;
		backwalkclip.playback = playback;
		backwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerBack01")->GetMeshes()[0]);
		backwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerBack")->GetMeshes()[0]);
		backwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerBack02")->GetMeshes()[0]);

		animator->AddAnimationClip("WalkBack", backwalkclip);


		AnimationClip leftwalkclip;
		leftwalkclip.playback = playback;
		leftwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerLeft01")->GetMeshes()[0]);
		leftwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerLeft02")->GetMeshes()[0]);

		animator->AddAnimationClip("WalkLeft", leftwalkclip);


		AnimationClip rightwalkclip;
		rightwalkclip.playback = playback;
		rightwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerRight01")->GetMeshes()[0]);
		rightwalkclip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("PlayerRight02")->GetMeshes()[0]);

		animator->AddAnimationClip("WalkRight", rightwalkclip);




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

		MeshComponent* meshComp = nullptr;

		if (mesh)
		{
			meshComp = &enemyEntity.AddComponent<MeshComponent>(mesh);
			enemyEntity.AddComponent<MeshRenderer>();
		}


		enemy = &enemyEntity.AddComponent<Enemy>(type,rigidBody);

		Animator* animator = &enemyEntity.AddComponent<Animator>();

		if (meshComp)
		{
			animator->SetMeshComponentRef(meshComp);
			enemy->SetAnimtor(animator);
		}

		AnimationClip clip;
		

		switch (type)
		{
		case Robotron::EnemyType::Grunt:
			
			clip.framelist.clear();
			
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("GruntWalk01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Grunt")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("GruntWalk02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Grunt")->GetMeshes()[0]);
			clip.playback = 0.2f;


			animator->AddAnimationClip("Walk",clip);

			break;
		case Robotron::EnemyType::Spheroid:
			break;
		case Robotron::EnemyType::Enforcer:
			break;
		case Robotron::EnemyType::Hulk:

			clip.playback = 0.2f;

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkFront01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Hulk")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkFront02")->GetMeshes()[0]);

			animator->AddAnimationClip("Walk", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkLeft")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkLeft01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkLeft02")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkLeft", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkRight")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkRight01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("HulkRight02")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkRight", clip);




			break;
		case Robotron::EnemyType::Brain:
			break;
		default:
			break;
		}


		

		

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


		MeshComponent* meshComp = nullptr;

		if (mesh)
		{	meshComp = &humanEntity.AddComponent<MeshComponent>(mesh);
			humanEntity.AddComponent<MeshRenderer>();
		}


		human = &humanEntity.AddComponent<Human>(type, rigidBody);


		Animator* animator = &humanEntity.AddComponent<Animator>();

		if (meshComp)
		{
			animator->SetMeshComponentRef(meshComp);
			human->SetAnimtor(animator);
		}

		AnimationClip clip;

		switch (type)
		{
		case Robotron::HumanType::None:
			break;
		case Robotron::HumanType::Daddy: 
			clip.playback = 0.2f;

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyRight01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyRight")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyRight02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyRight")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkRight", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyLeft01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyLeft")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyLeft02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyLeft")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkLeft", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyFront01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Daddy")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyFront02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Daddy")->GetMeshes()[0]);

			animator->AddAnimationClip("Walk", clip);


			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyBack01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyBack")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyBack02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("DaddyBack")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkBack", clip);

			break;
		case Robotron::HumanType::Mommy:
			break;
		case Robotron::HumanType::Mikey:

			clip.playback = 0.2f;

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyRight01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyRight")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyRight02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyRight")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkRight", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyLeft01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyLeft")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyLeft02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyLeft")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkLeft", clip);

			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyFront01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Mikey")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyFront02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("Mikey")->GetMeshes()[0]);

			animator->AddAnimationClip("Walk", clip);


			clip.framelist.clear();

			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyBack01")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyBack")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyBack02")->GetMeshes()[0]);
			clip.framelist.push_back(Application::GetCurrent().GetModelLibrary()->GetResource("MikeyBack")->GetMeshes()[0]);

			animator->AddAnimationClip("WalkBack", clip);
			break;
		default:
			break;
		}

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

		model = modelLib->LoadModel("PlayerFront01", "Assets//PlayerFront01.ply");
		model = modelLib->LoadModel("PlayerFront02", "Assets//PlayerFront02.ply");

		model = modelLib->LoadModel("PlayerLeft01", "Assets//PlayerLeft01.ply");
		model = modelLib->LoadModel("PlayerLeft02", "Assets//PlayerLeft02.ply");

		model = modelLib->LoadModel("PlayerRight01", "Assets//PlayerRight01.ply");
		model = modelLib->LoadModel("PlayerRight02", "Assets//PlayerRight02.ply");

		model = modelLib->LoadModel("PlayerBack", "Assets//PlayerBack.ply");
		model = modelLib->LoadModel("PlayerBack01", "Assets//PlayerBack01.ply");
		model = modelLib->LoadModel("PlayerBack02", "Assets//PlayerBack02.ply");


		model = modelLib->LoadModel("Grunt", "Assets//grunt1.ply");
		gruntMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("GruntWalk01", "Assets//grunt2.ply");
		model = modelLib->LoadModel("GruntWalk02", "Assets//grunt3.ply");


		model = modelLib->LoadModel("Hulk", "Assets//hulkFront.ply");
		hulkMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("HulkFront01", "Assets//hulkFront01.ply");
		model = modelLib->LoadModel("HulkFront02", "Assets//hulkFront02.ply");
		model = modelLib->LoadModel("HulkLeft", "Assets//hulkLeft.ply");
		model = modelLib->LoadModel("HulkLeft01", "Assets//hulkLeft01.ply");
		model = modelLib->LoadModel("HulkLeft02", "Assets//hulkLeft02.ply");
		model = modelLib->LoadModel("HulkRight", "Assets//hulkRight.ply");
		model = modelLib->LoadModel("HulkRight01", "Assets//hulkRight01.ply");
		model = modelLib->LoadModel("HulkRight02", "Assets//hulkRight02.ply");

		model = modelLib->LoadModel("Enforcer", "Assets//Enforcer.ply");
		enforcerMesh = model->GetMeshes()[0];


		model = modelLib->LoadModel("Daddy", "Assets//daddyFront.ply");
		daddyMesh = model->GetMeshes()[0];
		model = modelLib->LoadModel("DaddyFront01", "Assets//daddyFront01.ply");
		model = modelLib->LoadModel("DaddyFront02", "Assets//daddyFront02.ply");
		model = modelLib->LoadModel("DaddyLeft01", "Assets//daddyLeft01.ply");
		model = modelLib->LoadModel("DaddyLeft02", "Assets//daddyLeft02.ply");
		model = modelLib->LoadModel("DaddyLeft", "Assets//daddyLeft.ply");

		model = modelLib->LoadModel("DaddyRight01", "Assets//daddyRight01.ply");
		model = modelLib->LoadModel("DaddyRight02", "Assets//daddyRight02.ply");
		model = modelLib->LoadModel("DaddyRight", "Assets//daddyRight.ply");

		model = modelLib->LoadModel("DaddyBack01", "Assets//daddyBack01.ply");
		model = modelLib->LoadModel("DaddyBack02", "Assets//daddyBack02.ply");
		model = modelLib->LoadModel("DaddyBack", "Assets//daddyBack.ply");


		model = modelLib->LoadModel("Mommy", "Assets//MommyFront.ply");
		mommyMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("Mikey", "Assets//mikeyFront.ply");
		mikeyMesh = model->GetMeshes()[0];

		model = modelLib->LoadModel("MikeyFront01", "Assets//mikeyFront01.ply");
		model = modelLib->LoadModel("MikeyFront02", "Assets//mikeyFront02.ply");
		model = modelLib->LoadModel("MikeyLeft01", "Assets//mikeyLeft01.ply");
		model = modelLib->LoadModel("MikeyLeft02", "Assets//mikeyLeft02.ply");
		model = modelLib->LoadModel("MikeyLeft", "Assets//mikeyLeft.ply");

		model = modelLib->LoadModel("MikeyRight01", "Assets//mikeyRight01.ply");
		model = modelLib->LoadModel("MikeyRight02", "Assets//mikeyRight02.ply");
		model = modelLib->LoadModel("MikeyRight", "Assets//mikeyRight.ply");

		model = modelLib->LoadModel("MikeyBack01", "Assets//mikeyBack01.ply");
		model = modelLib->LoadModel("MikeyBack02", "Assets//mikeyBack02.ply");
		model = modelLib->LoadModel("MikeyBack", "Assets//mikeyBack.ply");



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