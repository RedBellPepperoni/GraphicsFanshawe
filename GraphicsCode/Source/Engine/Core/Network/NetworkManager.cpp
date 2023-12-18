#include "NetworkManager.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Scene/Scene.h"
#include "NetworkComponent.h"


#define SERVER_PORT 8468
#define SERVER_IP "127.0.0.1"

namespace FanshaweGameEngine {

	namespace Network
	{

		// Move this to a structure for each client
		sockaddr_in addr;
		int addrLen;

		class Buffer
		{
		public:
			Buffer() { }
			~Buffer() { }

			std::vector<uint8_t> data;
		};

		NetworkManager::NetworkManager()
		{
		}

		NetworkManager::~NetworkManager()
		{

		}

		void NetworkManager::Initialize()
		{
			// Initialize WinSock
			WSADATA wsaData;
			int result;

			// Set version 2.2 with MAKEWORD(2,2)
			result = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (result != 0) {
				printf("WSAStartup failed with error %d\n", result);
				return;
			}
			printf("WSAStartup successfully!\n");


			// Socket
			m_ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (m_ServerSocket == INVALID_SOCKET) {
				printf("socket failed with error %d\n", WSAGetLastError());
				WSACleanup();
				return;
			}
			printf("socket created successfully!\n");

			unsigned long nonblock = 1;
			result = ioctlsocket(m_ServerSocket, FIONBIO, &nonblock);
			if (result == SOCKET_ERROR) {
				printf("set nonblocking failed with error %d\n", result);
				return;
			}
			printf("set nonblocking successfully!\n");

			m_ServerAddr.sin_family = AF_INET;
			m_ServerAddr.sin_port = htons(SERVER_PORT);
			m_ServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
			m_ServerAddrLen = sizeof(m_ServerAddr);

			printf("NetworkManager running...\n");

			//m_NextSendTime = std::chrono::high_resolution_clock::now();

			m_NetworkedPositions.resize(NUM_PLAYERS);

			m_Initialized = true;
		}

		void NetworkManager::Destroy()
		{
			if (!m_Initialized)
			{
				return;
			}

			closesocket(m_ServerSocket);
			WSACleanup();

			m_Initialized = false;
		}

		void NetworkManager::Update(float deltatime)
		{
			if (!m_Initialized)
			{
				return;
			}

			// Send information/data back to clients
			SendDataToServer(deltatime);

			// Handle all recv data
			HandleRECV();

			// Process everything

		/*	LOG_INFO("Sizw : {0}, ", sizeof(PlayerData));
			LOG_INFO("Size INT32 : {0} || Size int8 : {1} ", sizeof(int32_t), sizeof(int8_t));*/

			


		}

		void NetworkManager::SendPlayerData(Vector3 position,Vector3 direction)
		{
			int32_t XPosition = (position.x * 100.0f);
			int32_t ZPosition = (position.z * 100.0f);

			uint8_t XDirection = (direction.x * 100.0f);
			uint8_t ZDirection = (direction.z * 100.0f);


			m_playerData.positionX = XPosition;
			m_playerData.positionZ = ZPosition;

			m_playerData.directionX = XDirection;
			m_playerData.directionZ = ZDirection;


		}

		void NetworkManager::HandleRECV()
		{

			// Read
			const int bufLen = 10 * 2 * NUM_PLAYERS;
			char buffer[bufLen];
			int result = recvfrom(m_ServerSocket, buffer, bufLen, 0, (sockaddr*)&m_ServerAddr, &m_ServerAddrLen);
			if (result == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// Not a real error, we expect this.
					// -1 is an error, 0 is disconnected, >0 is a message
					// WSA uses this as a flag to check if it is a real error
					return;
				}

				return;
			}


			memcpy(&m_NetworkedPositions[0].positionX, (int32_t*)&(buffer[0]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[0].positionZ, (int32_t*)&(buffer[4]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[0].directionX, (int8_t*)&(buffer[8]), sizeof(int8_t));
			memcpy(&m_NetworkedPositions[0].directionZ, (int8_t*)&(buffer[9]), sizeof(int8_t));


			memcpy(&m_NetworkedPositions[1].positionX, &(buffer[10]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[1].positionZ, &(buffer[14]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[1].directionX, &(buffer[18]), sizeof(int8_t));
			memcpy(&m_NetworkedPositions[1].directionZ, &(buffer[19]), sizeof(int8_t));


			/*LOG_INFO("Position : {0}, {1}", m_NetworkedPositions[1].positionX, m_NetworkedPositions[1].positionZ);*/
			

			memcpy(&m_NetworkedPositions[2].positionX, (int32_t*)&(buffer[20]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[2].positionZ, (int32_t*)&(buffer[24]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[2].directionX, (int8_t * )&(buffer[28]), sizeof(int8_t));
			memcpy(&m_NetworkedPositions[2].directionZ, (int8_t * )&(buffer[29]), sizeof(int8_t));
			
			memcpy(&m_NetworkedPositions[3].positionX, (int32_t*)&(buffer[30]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[3].positionZ, (int32_t*)&(buffer[34]), sizeof(int32_t));
			memcpy(&m_NetworkedPositions[3].directionX, (int8_t * )&(buffer[38]), sizeof(int8_t));
			memcpy(&m_NetworkedPositions[3].directionZ, (int8_t * )&(buffer[39]), sizeof(int8_t));;
		}

		void NetworkManager::SendDataToServer(float deltatime)
		{
			/*std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
			if (m_NextSendTime > currentTime)
			{
				return;
			}

			m_NextSendTime = currentTime + std::chrono::milliseconds(50);*/

			// Add 20 ms to the next broadcast time from now()
			//m_NextBroadcastTime 


			currenttime = currenttime + deltatime;

			if (currenttime < m_Wait)
			{
				return;
			}

			currenttime = 0.0f;


		


			// MessageQueue, loop through and send all messages
			// You may multiple servers, you are sending data to
			int result = sendto(m_ServerSocket, (const char*)&m_playerData,
				sizeof(m_playerData), 0, (SOCKADDR*)&m_ServerAddr, m_ServerAddrLen);
			if (result == SOCKET_ERROR) {
				// TODO: We want to handle this differently.
				printf("send failed with error %d\n", WSAGetLastError());
				Destroy();
				return;
			}
		}
	}
}