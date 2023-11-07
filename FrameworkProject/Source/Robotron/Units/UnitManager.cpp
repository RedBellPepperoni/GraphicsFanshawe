#include "UnitManager.h"
#include "Enemy.h"
#include "Player.h"
#include "UnitSpawner.h"

namespace Robotron
{

	Player* UnitManager::playerRef = nullptr;

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

	void UnitManager::LoadLevel(int levelId)
	{
		if (m_levelDataList.empty() || levelId >= m_levelDataList.size())
		{
			LOG_ERROR("Out of bound on Level Data");
			return;
		}

		LevelData levelData = m_levelDataList[levelId];

		
		playerRef = m_spawner->SpawnPlayer();


		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(0.0f, 0.0f, 5.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(10.0f, 0.0f, 5.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(15.0f, 0.0f, 5.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(20.0f, 0.0f, 6.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(25.0f, 0.0f, 5.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(30.0f, 0.0f, 6.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(35.0f, 0.0f, 5.0f)));

		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(5.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(10.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(15.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(20.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(25.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(30.0f, 0.0f, 0.0f)));
		m_enemyUnits.push_back(m_spawner->SpawnEnemy(EnemyType::Grunt, Vector3(35.0f, 0.0f, 0.0f)));



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




	}

	Vector2 UnitManager::GetPlayerPos()
	{
		return playerRef->GetPosition();
	}

}