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
		level01.humanCount = 0;

		m_levelDataList.push_back(level01);


	

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


		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(10.0f, 0.0f, 5.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(-10.0f, 0.0f, -15.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Hulk, Vector3(15.0f, 0.0f, 5.0f)));


		
		m_Humans.push_back(m_spawner->SpawnHuman(HumanType::Daddy, Vector3(0.0f, 0.0f, -10.0f)));



		/*grunt = m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(15.0f, 0.0f, 5.0f));
		m_allUnits.push_back((BaseUnit*)(grunt));*/

	}

	void UnitManager::Update(float deltaTime)
	{

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




	}

}