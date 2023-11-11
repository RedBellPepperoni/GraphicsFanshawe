#include "UnitManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Human.h"
#include "UnitSpawner.h"

namespace Robotron
{

	Player* UnitManager::playerRef = nullptr;
	ArenaImpl* UnitManager::arena = nullptr;

	
	
	

	void UnitManager::Init()
	{
		m_spawner = Factory<UnitSpawner>::Create();

		m_spawner->LoadMeshes();

		LevelData level01;
		level01.enforcerCount = 0;
		level01.gruntCount = 4;
		level01.humanCount = 5;

		m_levelDataList.push_back(level01);

		m_spawner->SpawnMesh("GameWin",Vector3(-400.0f,0.0f,-400.0f), Vector3(0.15f), Vector3(0.0f,180.0f,0.0f));
		m_spawner->SpawnMesh("Gameover",Vector3(400.0f,0.0f,400.0f), Vector3(0.15f), Vector3(0.0f, 180.0f, 0.0f));
	
		Application::GetCurrent().GetCurrentScene()->SetMainCameraPosition(Vector3(0.0f, 50.0f, 0.0f));

	}

	void UnitManager::SetArena(ArenaImpl* ptr)
	{
		arena = ptr;
	}

	void UnitManager::LoadLevel(int levelId)
	{
		if (m_levelDataList.empty() || levelId >= m_levelDataList.size())
		{
			LOG_ERROR("Out of bound on Level Data");
			return;
		}

		LevelData levelData = m_levelDataList[levelId];

		

		playerRef = m_spawner->SpawnPlayer();

		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Enforcer, Vector3(-35.0f, 0.0f, 10.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Enforcer, Vector3(-10.0, 0.0f, -18.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Enforcer, Vector3(35.0f, 0.0f, 19.0f)));


		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(-35.0f, 0.0f, -10.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(-10.0f, 0.0f, -15.0f)));


		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Hulk, Vector3(20.0f, 0.0f, 15.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Hulk, Vector3(15.0f, 0.0f, 5.0f)));

		
		hulkCount = 2;



		
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Daddy, Vector3(30.0f, 0.0f, -16.0f)));
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Mommy, Vector3(0.0f, 0.0f, -10.0f)));
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Mikey, Vector3(-30.0f, 0.0f, 10.0f)));
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Mikey, Vector3(-30.0f, 0.0f, -18.0f)));
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Mikey, Vector3(-30.0f, 0.0f, 19.0f)));




		displayList.push_back(SpawnDisplayItem(DisplayType::Score1000, Vector2(100.0f)));
		displayList.push_back(SpawnDisplayItem(DisplayType::Score2000, Vector2(100.0f)));
		displayList.push_back(SpawnDisplayItem(DisplayType::Score3000, Vector2(100.0f)));
		displayList.push_back(SpawnDisplayItem(DisplayType::Score4000, Vector2(100.0f)));
		displayList.push_back(SpawnDisplayItem(DisplayType::Score5000, Vector2(100.0f)));
		displayList.push_back(SpawnDisplayItem(DisplayType::HumanDeath, Vector2(100.0f)));


		enemyCount = m_enemyUnits.size();
		humanCount = m_Humans.size();

	}

	void UnitManager::Update(float deltaTime)
	{

		if(GameOver)
		{
			return;
		}

		m_enemyUnits;

		playerRef->Update(deltaTime);

		for (Enemy* unit : m_enemyUnits)
		{
			unit->Update(deltaTime);
		}

		for (Human* human : m_Humans)
		{
			human->Update(deltaTime);
		}



		if (!displayList.empty())
		{

			displayList;

			for (DisplayItem* item : displayList)
			{
				item->Update(deltaTime);
			}
		}
	}

	Vector2 UnitManager::GetPlayerPos()
	{
		return playerRef->GetPosition();
	}

	Vector2 UnitManager::GetRandomPosition()
	{

		if (!arena)
		{
			return Vector2(0.0f);
		}



		return arena->GetRandomPointinArena();
	}

	void UnitManager::EnemyKilled(EnemyType type)
	{
		// Decrement the Counter
		enemyCount -= 1;

		CheckGameStatus();


	}

	Vector2 UnitManager::GetHumanPosition()
	{
		if (m_Humans.empty())
		{
			return GetPlayerPos();
		}
		else
		{
			return m_Humans[0]->GetPosition();
		}

		
	}


	

	DisplayItem* UnitManager::SpawnDisplayItem(DisplayType type, Vector2 position)
	{

		DisplayItem* item = nullptr;

		Entity itemEntity = Application::GetCurrent().GetCurrentScene()->CreateEntity("Display");

	
		
    	Transform* transform = &itemEntity.AddComponent<Transform>();

		transform->SetScale(Vector3(0.025f));
		transform->SetPosition(Vector3(position.x,0.0f,position.y));
		transform->SetRotation(Vector3(-90.0f, 0.0f, 0.0f));


		item = &itemEntity.AddComponent<DisplayItem>();


		SharedPtr<Mesh> mesh = nullptr;

		switch (type)
		{
		case Robotron::Score1000: mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Score1000")->GetMeshes()[0];
			break;
		case Robotron::Score2000:  mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Score2000")->GetMeshes()[0];
			
			break;
		case Robotron::Score3000:  mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Score3000")->GetMeshes()[0];
			break;
		case Robotron::Score4000:  mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Score4000")->GetMeshes()[0];
			break;
		case Robotron::Score5000:  mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Score5000")->GetMeshes()[0];
			break;
		case Robotron::HumanDeath:  mesh = Application::GetCurrent().GetModelLibrary()->GetResource("Skull")->GetMeshes()[0];
			break;
		default:
			break;
		}

		if (!mesh)
		{
			return item;
		}

		MeshComponent* comp = &itemEntity.AddComponent<MeshComponent>(mesh);
		itemEntity.AddComponent<MeshRenderer>();

		item->Setup(comp, transform);

		return item;
		
	}

	void UnitManager::ShowDisplayItem(DisplayType type, Vector2 position)
	{
		int i = 0;

		switch (type)
		{
		case Robotron::Score1000: i = 0;
			break;
		case Robotron::Score2000: i = 1;
			break;
		case Robotron::Score3000: i = 2;
			break;
		case Robotron::Score4000: i = 3;
			break;
		case Robotron::Score5000: i = 4;
			break;
		case Robotron::HumanDeath: i = 5;
			break;
		default:
			break;
		}

		displayList[i]->Display(position);

	}

	

	

	void UnitManager::SetHumaRescued()
	{
		// Spawn Score here

		humanPickupCount++;
		humanCount--;

		CheckGameStatus();

		if (humanCount < 0) { humanCount = 0; }

			switch (humanPickupCount)
			{
			case 1:  ShowDisplayItem(DisplayType::Score1000, GetPlayerPos());
				break;

			case 2: ShowDisplayItem(DisplayType::Score2000, GetPlayerPos());
				break;

			case 3: ShowDisplayItem(DisplayType::Score3000, GetPlayerPos());
				break;

			case 4: ShowDisplayItem(DisplayType::Score4000, GetPlayerPos());
				break;

			case 5: ShowDisplayItem(DisplayType::Score5000, GetPlayerPos());
				break;


			default:
				break;
			}

		
	}

	void UnitManager::SetHumanDead(Vector2 deathPosition, bool becameProg)
	{
			humanCount--;
			ShowDisplayItem(DisplayType::HumanDeath, deathPosition);
			CheckGameStatus();

			if (humanCount < 0) { humanCount = 0; }
		
	}

	void UnitManager::SetGameOver(bool winCondition)
	{
		GameOver = true;

		if (winCondition)
		{
			Application::GetCurrent().GetCurrentScene()->SetMainCameraPosition(Vector3(-400.0f, 50.0f, -400.0f));
		}

		else
		{
			Application::GetCurrent().GetCurrentScene()->SetMainCameraPosition(Vector3(400.0f, 50.0f, 400.0f));
		}

		
	}

	bool UnitManager::CheckGameStatus()
	{
		//LOG_WARN("EnemyCount : {0} || HumanCount : {1}", enemyCount, humanCount);

		if (enemyCount <= hulkCount && humanCount <= 0)
		{
			
			SetGameOver(true);
			return true;
		}

		return  false;
	}

	
}