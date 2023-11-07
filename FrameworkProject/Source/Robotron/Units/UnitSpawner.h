#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/Math.h"
#include <stdint.h>
#include <vector>

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Mesh;
	}
}

using FanshaweGameEngine::Rendering::Mesh;
using namespace FanshaweGameEngine::Math;


namespace Robotron
{

	class Player;
	class Enemy;

	enum class EnemyType : uint8_t;

	class UnitSpawner
	{

	public:

		UnitSpawner();
		~UnitSpawner();


		Player* SpawnPlayer();
		Enemy* SpawnEnemy(EnemyType type,const Vector3& position);
		//BaseUnit* SpawnHuman();



		void LoadMeshes();


	private:


		SharedPtr<Mesh> playerMesh = nullptr;
		SharedPtr<Mesh> gruntMesh = nullptr;
		SharedPtr<Mesh> hulkMesh = nullptr;
		SharedPtr<Mesh> spheroidMesh = nullptr;
		SharedPtr<Mesh> enforcerMesh = nullptr;
		SharedPtr<Mesh> humanMesh = nullptr;
		




	};
}