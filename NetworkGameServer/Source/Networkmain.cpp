#include "NetworkServer.h"

#include <conio.h>

int main(int atgc, char** argv)
{
	bool isRunning = true;

	NetworkServer networkManager;

	networkManager.Initialize();


	while (isRunning)
	{

		networkManager.Update();


		if (_kbhit())
		{
			if (_getch() == 27)
			{
				isRunning = false;
			}
		}
	}


	networkManager.Destroy();




 return 0;



}