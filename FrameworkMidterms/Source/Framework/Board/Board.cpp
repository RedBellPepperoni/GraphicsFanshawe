#include "Framework/Board/Board.h"
#include "Engine/Utils/Loading/File.h"
#include "Engine/Utils/Logging/Log.h"
#include <fstream>

namespace Framework 
{
	Board::Board()
	{

	}

	Framework::Board::~Board()
	{

	}

	bool Framework::Board::GenerateBoardfromTextFile(const std::string& filename)
	{

		// hardcoding for now
		uint32_t maxXcells = 0;
		uint32_t maxYcells = 0;



		//===== NOTE =====


		/*
		
		Read it line by line instead of a string stream tomorrow
		
		*/


		std::fstream mapFile;
		std::string line;
		char key = 'X';

		int mapPositionIndex = 0;

		


		//open a file to perform read operation using file object
		mapFile.open(filename, std::ios::in); 


		// new lines will be skipped unless we stop it from happening:    
		mapFile.unsetf(std::ios_base::skipws);

		// count the newlines with an algorithm specialized for counting:
		unsigned lineCount =
			std::count(
				std::istream_iterator<char>(mapFile),
				std::istream_iterator<char>(),
				'\n');


		mapFile.close();

		//open a file to perform read operation using file object
		mapFile.open(filename, std::ios::in);
		


		maxYcells = lineCount;

		//checking whether the file is open
		if (mapFile.is_open()) 
		{   
			std::string lineData;
			uint16_t lineCounter = 0;

			for (uint16_t yIndex = 0; yIndex < maxYcells; yIndex++)
			{

				std::getline(mapFile, lineData);

			    maxXcells = lineData.length();


				for (uint16_t xIndex = 0; xIndex <= maxXcells; xIndex++)
				{

					key = lineData[xIndex];

					CellPos pos = CellPos(xIndex, yIndex);
					CellData data = CellData(CellState::None, pos);


					if (key == 'X')
					{
						data.state = CellState::Wall;
					}

					// hard coding space char
					else if (key == 0x20)
					{
						// Special case
						if (yIndex == 0 || xIndex == 0 || yIndex == maxYcells || xIndex == maxXcells)
						{
							data.state = CellState::Exit;
						}

						else 
						{
							data.state = CellState::Empty;
						}

					}



					m_boardGrid.emplace(mapPositionIndex, data);

					mapPositionIndex++;

				}

			}

			// Update the rows and Columns
			totalColumns = maxXcells;
			totalRows = maxYcells;
			

			mapFile.close(); //close the file object.
	
			
			return true;

			


		}

		else
		{
			return false;
		}


		// ====================== FIRST LINE ===================

		

	}

	CellData Board::GetDirectedMovement(const Vector2Int& selfPos, const Vector2Int& targetPos)
	{


		int outcellIndex = selfPos.y * (totalColumns + 1) + selfPos.x;

		CellData currentCell;

		CellData outData;

		CellState state;
		

		std::vector<CellData> availableCells;


		auto iterator = m_boardGrid.find(outcellIndex);

		if (iterator == m_boardGrid.end())
		{
			return CellData();
		}

		currentCell = iterator->second;

		CellPos averagepos = currentCell.position;

		bool CanMove = false;
		
		bool walldetected = false;
		


		if ((selfPos.x - targetPos.x) > 1)
		{
			// We have to move Left
			walldetected = false;

			int tempPos  = averagepos.x - 1 ;

			if (averagepos.x >= 0 && averagepos.y >= 0)
			{
				int checkIndex = GetIndexFromPosition(CellPos(tempPos,averagepos.y));

				auto iterator = m_boardGrid.find(checkIndex);

				if (iterator != m_boardGrid.end())
				{
					if (iterator->second.state == CellState::Empty)
					{
						CanMove = CanMove || true;
;						averagepos.x = tempPos;

					}
					else {
						walldetected = true;
					}

				}
			}
		}

		if ((selfPos.y - targetPos.y) > 1)
		{
			// We have to move UP
			walldetected = false;

			int tempPos = averagepos.y + 1;


			if (averagepos.x >= 0 && averagepos.y >= 0)
			{
				int checkIndex = GetIndexFromPosition(CellPos(averagepos.x, tempPos));

				auto iterator = m_boardGrid.find(checkIndex);

				if (iterator != m_boardGrid.end())
				{


					if (iterator->second.state == CellState::Empty)
					{
						CanMove = CanMove || true;
						averagepos.y = tempPos;
					}
					else
					{
						walldetected = true;
					}


				}
			}
		}



		if (walldetected = true || ((selfPos.x - targetPos.x) < -1))
		{
			// We have to move Right

			walldetected = false;

			int tempPos =  averagepos.x + 1;

			if (averagepos.x >= 0 && averagepos.y >= 0)
			{
				int checkIndex = GetIndexFromPosition(CellPos(tempPos, averagepos.y));

				auto iterator = m_boardGrid.find(checkIndex);

				if (iterator != m_boardGrid.end())
				{
					if (iterator->second.state == CellState::Empty)
					{
						//Reset it
						CanMove = CanMove || true;
						averagepos.x = tempPos;
						
					}

					else
					{
						walldetected = true;
					}

				}
			}
		}

		


		if(walldetected == true || ((selfPos.y - targetPos.y) < -1))
		{
			// We have to move UP
			walldetected = false;

			int tempPos = averagepos.y - 1;

			if (averagepos.x >= 0 && averagepos.y >= 0)
			{
				int checkIndex = GetIndexFromPosition(CellPos(averagepos.x, tempPos));

				auto iterator = m_boardGrid.find(checkIndex);

				if (iterator != m_boardGrid.end())
				{
					if (iterator->second.state == CellState::Empty)
					{
						CanMove = CanMove || true;
						averagepos.y = tempPos;
					}
					else
					{
						walldetected = true;
					}


				}
			}
		}
		

		outData.position = averagepos;
		//outData.state = ;

		if (CanMove)
		{
			outData.state = CellState::Empty;
		}
		else
		{
			outData.state = CellState::Wall;

		}

		return outData;
	}




	void Board::SetOccupyindex(const int cellIndex, int occupyindex)
	{
		m_boardGrid[cellIndex].occupyIndex = occupyindex;

		//LOG_ERROR("{0}",)
	}

	Vector3 Board::ConvertGridToWorld(const Vector2Int& position)
	{
		Vector3 outPosition = Vector3(0.0f);
	
		outPosition = Vector3(position.x , 1.0f, position.y + 0.5f );


		return outPosition;
	}

	// For now Random Movement
	CellData Board::GetRandomMovementCell(const Vector2Int& position)
	{
		

		int outcellIndex = position.y * (totalColumns + 1) + position.x;

		
		CellData currentCell;

		std::vector<CellData> availableCells;

		
		auto iterator = m_boardGrid.find(outcellIndex);

		if (iterator == m_boardGrid.end())
		{
			return CellData();
		}

		currentCell = iterator->second;
		

		CellPos CellLeft = CellPos(currentCell.position.x - 1, currentCell.position.y);

		if (CellLeft.x >= 0 && CellLeft.y >= 0)
		{
			int checkIndex = GetIndexFromPosition(CellLeft);

			auto iterator = m_boardGrid.find(checkIndex);

			if (iterator != m_boardGrid.end())
			{
				if (iterator->second.state == CellState::Empty)
				{		
					availableCells.push_back(iterator->second);
				}

			
			}
		}


		CellPos CellAbove = CellPos(currentCell.position.x, currentCell.position.y - 1);

		if (CellAbove.x >= 0 && CellAbove.y >= 0)
		{
			int checkIndex = GetIndexFromPosition(CellAbove);

			auto iterator = m_boardGrid.find(checkIndex);

			if (iterator != m_boardGrid.end())
			{
				if (iterator->second.state == CellState::Empty)
				{
					availableCells.push_back(iterator->second);
				}

				

				
			}
		
		}

		CellPos CellBelow = CellPos(currentCell.position.x, currentCell.position.y + 1);

		if (CellBelow.x >= 0 && CellBelow.y >= 0)
		{
			int checkIndex = GetIndexFromPosition(CellBelow);

			auto iterator = m_boardGrid.find(checkIndex);

			if (iterator != m_boardGrid.end())
			{
				if (iterator->second.state == CellState::Empty)
				{
					
					availableCells.push_back(iterator->second);
				}
				
			}

		}

		CellPos CellRight = CellPos(currentCell.position.x + 1, currentCell.position.y);

		if (CellRight.x >= 0 && CellRight.y >= 0)
		{
			int checkIndex = GetIndexFromPosition(CellRight);

			auto iterator = m_boardGrid.find(checkIndex);

			if (iterator != m_boardGrid.end() )
			{
				if (iterator->second.state == CellState::Empty)
				{
					availableCells.push_back(iterator->second);

				}
				
			}
		}
		
		if (availableCells.empty())
		{
			return CellData();
		}
	
		int randomIndex = (rand() % (availableCells.size()));
	

		return  availableCells[randomIndex];


	}

	int Board::GetIndexFromPosition(CellPos position)
	{
		int index = position.y * (totalColumns + 1) + position.x;

		return index;
	}

}
