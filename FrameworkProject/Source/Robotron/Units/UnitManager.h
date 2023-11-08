#pragma once
#include <stdint.h>
#include <vector>
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Robotron/Arena/ArenaImpl.h"

namespace Robotron
{
	class UnitSpawner;
	class Enemy;
	class Player;
	class Human;
	class BaseUnit;

	enum class EnemyType : uint8_t;

	struct LevelData
	{
		uint8_t gruntCount = 0;
		uint8_t enforcerCount = 0;
		uint8_t humanCount = 0;

	};

	using namespace FanshaweGameEngine::Math;


	class UnitManager
	{
	public:

		UnitManager() {};
		~UnitManager() {};

		void Init();

		void SetArena(ArenaImpl* ptr);

		void LoadLevel(int levelId);

		void Update(float deltaTime);

		static Vector2 GetPlayerPos();

		static Vector2 GetRandomPosition();

		void EnemyKilled(EnemyType type);


	private:

		SharedPtr<UnitSpawner> m_spawner = nullptr;




		std::vector<LevelData> m_levelDataList;

		std::vector<Enemy*> m_enemyUnits;

		std::vector<Human*> m_Humans;
		

		int enemyCount = 0;

		static Player* playerRef;
		static ArenaImpl* arena;

	};
}

