#pragma once
#include <stdint.h>
#include <vector>
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"

namespace Robotron
{
	class UnitSpawner;
	class Enemy;
	class Player;
	class Human;
	class BaseUnit;

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

		void LoadLevel(int levelId);

		void Update(float deltaTime);

		static Vector2 GetPlayerPos();


	private:

		SharedPtr<UnitSpawner> m_spawner = nullptr;


		std::vector<LevelData> m_levelDataList;

		std::vector<Enemy*> m_enemyUnits;
		

		static Player* playerRef;

	};
}

