#pragma once
#include <string>
#include "Engine/Utils/Math.h"
#include <vector>

using namespace FanshaweGameEngine;

namespace Framework
{
	


	enum class CellState : uint8_t
	{
		Wall, // Robots cant move ot these /pass through these
		Exit, // an extracase incase needed lateron -> for now it will be treaded as if its a wall
		Free, // Robots can move to these
		Occupied // Already occupied by something (mostly a robot)
	};

	struct CellPos
	{
		CellPos()
		{
			xPos = (-1);
			yPos = (-1);
		}

		CellPos(int x, int y)
		{
			xPos = x;
			yPos = y;
		}

		bool operator==(const CellPos& other)
		{
			return xPos == other.xPos && yPos == other.yPos;
		}


		int xPos;
		int yPos;
	};


	struct CellData
	{
		CellData()
		{
			state = (CellState::Free);
			position = CellPos(-1, -1);
		}

		CellData(CellState instate, CellPos inPos)
		{
			state = instate;
			position = inPos;
		}

		// Defines the current state of the cell
		CellState state;

		CellPos position;

		// Add the Robot refernce here later
		

	};

	



	

	class Board
	{


	public:

		


		Board();
		~Board();

		// Reads and fills in the data of the board from the text file
		bool GenerateBoardfromTextFile(const std::string& filename);

		std::vector<CellData> GetGrid() const { return m_grid; }





	private:

		// The Grid of the board
		
		std::vector<CellData> m_grid = {};



		

	};


}

