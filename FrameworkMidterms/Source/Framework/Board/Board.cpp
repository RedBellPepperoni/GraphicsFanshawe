#include "Framework/Board/Board.h"
#include "Engine/Utils/Loading/File.h"
#include <sstream>

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
		uint16_t maxXcells = 102;
		uint16_t maxYcells = 62;

		

		



		//===== NOTE =====


		/*
		
		Read it line by line instead of a string stream tomorrow
		
		*/


		//m_grid.

		// Assuming the file is in ASCII
	   // Loading the entire file to a tempstring
		std::string tempFile = File::ReadFileToString(filename);

		if (tempFile.empty())
		{
			// Model not loaded
			return false;
		}

		// Initializing the string stream with the loaded Text data
		std::istringstream stringStream(tempFile);

		std::string key;

		// ====================== FIRST LINE ===================

		for (uint16_t xIndex = 0; xIndex < maxXcells; xIndex++)
		{
			stringStream >> key;


			if (key == "X")
			{

				CellData data = CellData(CellState::Wall, CellPos(xIndex,0));

				m_grid.push_back(data);

			}

			else if (key == " ")
			{
				// special case for the 
				CellData data = CellData(CellState::Exit, CellPos(xIndex, 0));

				// Add the GridData
				m_grid.push_back(data);
			}
		}

	}

}
