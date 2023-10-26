#pragma once
#include "GameEngine.h" 
#include"Framework/Board/Board.h"
#include"Framework/Robot/Robot.h"

namespace Framework
{
	// the Brain that runs everything i guess
	class Game
	{

	public:

		Game();
		~Game();

		void Update(float deltaTime);

		void CreateRobot(const int friendId,const Vector2Int& position, const SharedPtr<Model>& model);

		void GenerateGameBoard(const std::string& filename);

		void Init();

	private:

		void UpdateTurn();

		

		Board m_board;

		float m_updateCounter = 0.0f;

		// 1.0 means it A new turn will happen every 1 second
	    float m_stepTimer = 1.0f;

	    uint32_t m_robotCount = 0;

		

	};
}

