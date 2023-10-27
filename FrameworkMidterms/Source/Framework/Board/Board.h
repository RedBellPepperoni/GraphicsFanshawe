#pragma once
#include <string>
#include "Engine/Utils/Math.h"
#include <vector>
#include <map>


using namespace FanshaweGameEngine;

namespace Framework
{
	


	enum class CellState : uint8_t
	{
		Wall, // Robots cant move ot these /pass through these
		Exit, // an extracase incase needed lateron -> for now it will be treaded as if its a wall
		Empty, // Robots can move to these
		Pillar,
		Occupied, // Already occupied by something (mostly a robot)
		None
	};

	struct CellPos
	{
		CellPos()
		{
			x = (-1);
			y = (-1);
		}

		CellPos(int newX, int newY)
		{
			x = newX;
			y = newY;
		}

		bool operator==(const CellPos& other)
		{
			return x == other.x && y == other.y;
		}


		int x;
		int y;
	};


	struct CellData
	{
		CellData()
		{
			state = (CellState::None);
			position = CellPos(-1, -1);
			occupyIndex = -1;
		}

		CellData(CellState instate, CellPos inPos)
		{
			state = instate;
			position = inPos;
			occupyIndex = -1;
		}

		// Defines the current state of the cell
		CellState state;
		CellPos position;

		// the RobotIndex
		int occupyIndex;

		// Add the Robot refernce here later
		

	};

	



	

	class Board
	{


	public:

		


		Board();
		~Board();

		// Reads and fills in the data of the board from the text file
		bool GenerateBoardfromTextFile(const std::string& filename);


		CellData GetDirectedMovement(const Vector2Int& selfPos, const Vector2Int& targetPos);

		//std::vector<>

		std::map<int, CellData> GetGrid()& { return m_boardGrid; }

		void SetOccupyindex(const int cellIndex, int occupyindex);

		Vector3 ConvertGridToWorld(const Vector2Int& position);
		CellData GetRandomMovementCell(const Vector2Int& position);
		int GetIndexFromPosition(CellPos position);






	private:


		

		
		


	private:




		

		std::map<int, CellData> m_boardGrid = {};

		uint32_t totalRows = 0;
		uint32_t totalColumns = 0;

		

	};


}

