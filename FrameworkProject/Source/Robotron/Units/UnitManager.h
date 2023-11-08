#pragma once
#include <stdint.h>
#include <vector>
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Robotron/Arena/ArenaImpl.h"
#include "Engine/Utils/Singleton.h"
#include "Robotron/Score/DisplayItem.h"

using namespace FanshaweGameEngine;

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

	enum DisplayType
	{
		Score1000,
		Score2000,
		Score3000,
		Score4000,
		Score5000,
		HumanDeath

	};


	using namespace FanshaweGameEngine::Math;


	class UnitManager : public Singleton<UnitManager>
	{
	public:

		

		void Init();

		void SetArena(ArenaImpl* ptr);

		void LoadLevel(int levelId);

		void Update(float deltaTime);

		static Vector2 GetPlayerPos();

		static Vector2 GetRandomPosition();

		void EnemyKilled(EnemyType type);

		Vector2 GetHumanPosition();


		DisplayItem* SpawnDisplayItem(DisplayType type, Vector2 position);
		
		void ShowDisplayItem(DisplayType type, Vector2 position);

		void SetHumaRescued();
		void SetHumanDead(Vector2 deathPosition, bool becameProg);
		
		void SetGameOver(bool winCondition);

	private:

		SharedPtr<UnitSpawner> m_spawner = nullptr;

		
		std::vector<DisplayItem*> displayList;

		std::vector<LevelData> m_levelDataList;

		std::vector<Enemy*> m_enemyUnits;

		std::vector<Human*> m_Humans;
		

		int enemyCount = 0;
		int humanCount = 0;

		static Player* playerRef;
		static ArenaImpl* arena;

		bool GameOver = false;

	};
}

