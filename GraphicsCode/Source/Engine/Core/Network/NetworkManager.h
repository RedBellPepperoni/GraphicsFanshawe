#pragma once
// WinSock2 Windows Sockets
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

// Need to link Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#include "Engine/Utils/Math.h"
#include <vector>

#include "Engine/Core/ECS/Components/Transform.h"
const int NUM_PLAYERS = 4;

namespace FanshaweGameEngine 
{

	namespace Network
	{

		struct PlayerData
		{
			int32_t positionX = 0;
			int32_t positionZ = 0;

			int8_t directionX = 0;
			int8_t directionZ = 0;

			bool ShotBullet = false;
		
		};


		struct BulletData
		{
			int32_t positionX = 0;
			int32_t positionZ = 0;

			int8_t directionX = 0;
			int8_t directionZ = 0;

			bool canShoot = true;
		};

		


		struct ClientInfo
		{
			sockaddr_in addr;
			int addrLen;
		};

		class NetworkManager
		{
		public:
			NetworkManager();
			~NetworkManager();

			void Initialize();
			void Destroy();

			void Update(float deltatime);

			void SendPlayerData(Vector3 position,Vector3 direction);

			// 
			// Positions of players
			std::vector<PlayerData> m_NetworkedPositions;

		private:
			void HandleRECV();
			void SendDataToServer(float deltatime);

			bool m_Initialized = false;
			bool m_Connected = false;
			float m_Wait = 0.1f;

			SOCKET m_ServerSocket;
			sockaddr_in m_ServerAddr;
			int m_ServerAddrLen = 0;


			PlayerData m_playerData; 



			float currenttime = 0.0f;
			//// 
			// 
			// 
			// 
			//// Time
			//std::chrono::high_resolution_clock::time_point m_NextSendTime;

			//
			// ConnectedClients
			std::vector<ClientInfo> m_ConnectedClients;

		};

		const float RETRY_TIME_MS = 10000;
	}
}