#include "Game.h"
#include <Engine/Core/ECS/EntityManager.h>


namespace Framework
{
	Game::Game()
	{
	}
	Game::~Game()
	{
	}


	void Game::Update(float deltaTime)
	{
		m_updateCounter += deltaTime;

		if (m_updateCounter >= m_stepTimer)
		{
			m_updateCounter = 0.0f;

			UpdateTurn();
		}

	}

	int Game::CreateRobot(const int friendId, const Vector2Int& position, const SharedPtr<Model>& model)
	{
		int robotId = m_robotCount;

		Entity robotObject = Application::GetCurrent().GetCurrentScene()->CreateEntity("Robot_" + std::to_string(m_robotCount));


		// Add a Trasnform. later make sure every spawnd entity has an auto attached transform
		robotObject.AddComponent<Transform>();

		if(model!=nullptr)
		{ 	
			// Set the First mesh reference as out mesh component
		// Later need to make this automatically generate entities for multiple meshes
			robotObject.AddComponent<MeshComponent>(model->GetMeshes()[0]);
			robotObject.AddComponent<MeshRenderer>();
		}
	
		robotObject.AddComponent<Robot>(m_robotCount, position);
		robotObject.GetComponent<Robot>().SetFriendId(friendId);


		
		robotObject.GetComponent<Robot>().SetShouldMove(true);
		

		//int index = m_board.GetIndexFromPosition(CellPos(position.x, position.y));

		//m_board.GetGrid()[index].occupyIndex = m_robotCount;

	    robotObject.GetComponent<Transform>().SetPosition(m_board.ConvertGridToWorld(position));

		robotObject.GetComponent<Transform>().SetRotation(Quaternion(Vector3(glm::radians(-90.0f), 0.0f, 0.0f)));
		robotObject.GetComponent<Transform>().SetScale(Vector3(0.08f));

		m_robotCount++;

		return robotId;


	}

	void Game::GenerateGameBoard(const std::string& filename)
	{
		m_board.GenerateBoardfromTextFile(filename);

		
	}


	void Game::Init()
	{
		

	}

	void Game::UpdateTurn()
	{
		entt::registry& registry = Application::GetCurrent().GetCurrentScene()->GetRegistry();

		// havent wrapped all the Entt functions into my calsses , so the current state looks like this

		auto robotView = registry.view<Robot>();
		auto transformView = registry.view<Transform>();
		auto meshRenderView = registry.view<MeshRenderer>();
	
		// Looping through all the entities that have the Robot component
		for (entt::entity robot : robotView)
		{
			Transform* transform = &transformView.get<Transform>(robot);
			Robot* bot = &robotView.get<Robot>(robot);

			MeshRenderer* meshRend = &meshRenderView.get<MeshRenderer>(robot);

			Vector2Int pos = bot->GetGridPostion();

			int cellIndex = 0;

			CellData data = m_board.GetMovementCell(pos, cellIndex);


			m_collisionSystem.CheckOtherRobotCollisions(*bot, *transform, *meshRend);


			if (!bot->ShouldMove())
			{
				continue;
			}

			
			if (data.state == CellState::Empty)
			{
				Vector2Int newPos = Vector2Int(data.position.x, data.position.y);

				//bot->UpdatePositon(newPos);
				transform->SetPosition(m_board.ConvertGridToWorld(newPos));
			}

		



		}
		
	}
}