#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/Math.h"
#include <stdint.h>
#include <vector>
#include <string>

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
	class Human;


	enum class EnemyType : uint8_t;
	enum class HumanType : uint8_t;

	class UnitSpawner
	{

	public:

		UnitSpawner();
		~UnitSpawner();


		Player* SpawnPlayer();
		Enemy* SpawnEnemy(EnemyType type,const Vector3& position);
		Human* SpawnHuman(HumanType type, const Vector3& position);

		

		void SpawnMesh(std::string name,const Vector3 position, const Vector3 scale, const Vector3 rotation = Vector3(0.0f));

		void LoadMeshes();


	private:


		SharedPtr<Mesh> playerMesh = nullptr;
		SharedPtr<Mesh> gruntMesh = nullptr;
		SharedPtr<Mesh> hulkMesh = nullptr;
		SharedPtr<Mesh> spheroidMesh = nullptr;
		SharedPtr<Mesh> enforcerMesh = nullptr;
		SharedPtr<Mesh> daddyMesh = nullptr;
		SharedPtr<Mesh> mommyMesh = nullptr;
		SharedPtr<Mesh> mikeyMesh = nullptr;
		




	};
}