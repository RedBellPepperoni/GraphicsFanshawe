#include "NetworkServer.h"


#define SERVER_PORT 8468
#define SERVER_IP "127.0.0.1"

#include <iostream>


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

NetworkServer::NetworkServer()
{
}

NetworkServer::~NetworkServer()
{

}

void NetworkServer::Initialize()
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
	m_ListenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	printf("socket created successfully!\n");

	// using sockaddr_in
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind 
	result = bind(m_ListenSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (result == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(m_ListenSocket);
		WSACleanup();
		return;
	}
	printf("bind was successful!\n");

	unsigned long nonblock = 1;
	result = ioctlsocket(m_ListenSocket, FIONBIO, &nonblock);
	if (result == SOCKET_ERROR) {
		printf("set socket to nonblocking failed with error %d\n", WSAGetLastError());
		closesocket(m_ListenSocket);
		WSACleanup();
		return;
	}
	printf("set socket to nonblocking was successful!\n");

	printf("NetworkManager running...\n");

	m_NextBroadcastTime = std::chrono::high_resolution_clock::now();

	m_Initialized = true;
}

void NetworkServer::Destroy()
{
	if (!m_Initialized)
	{
		return;
	}

	closesocket(m_ListenSocket);
	WSACleanup();

	m_Initialized = false;
}

void NetworkServer::Update()
{
	if (!m_Initialized)
	{
		return;
	}

	// Handle all recv data
	HandleRECV();

	// Process everything

	// Send information/data back to clients
	BroadcastUpdatesToClients();
}

void NetworkServer::HandleRECV()
{
	// Read
	sockaddr_in addr;
	int addrLen = sizeof(addr);

	const int bufLen = sizeof(PlayerData);	// recving 2 floats only
	char buffer[bufLen];
	int result = recvfrom(m_ListenSocket, buffer, bufLen, 0, (SOCKADDR*)&addr, &addrLen);
	if (result == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// Not a real error, we expect this.
			// -1 is an error, 0 is disconnected, >0 is a message
			// WSA uses this as a flag to check if it is a real error
			return;
		}
		else
		{
			// TODO: We want to handle this differently.
			printf("recvfrom failed with error %d\n", WSAGetLastError());
			//Destroy();
		
			for (int i = 0; i < m_ConnectedClients.size(); i++)
			{
			
				
				size_t last = m_ConnectedClients.size() - 1;


				if (addr.sin_addr.S_un.S_addr != m_ConnectedClients[i].addr.sin_addr.S_un.S_addr)
				{
					return;
				}

				if (i == last)
				{
					m_ConnectedClients.pop_back();
				}
				else
				{
					ClientInfo info = m_ConnectedClients[last];
					m_ConnectedClients[last] = m_ConnectedClients[i];
					m_ConnectedClients[i] = info;

					m_ConnectedClients.pop_back();
				}


				
			}




			return;
		}
	}

	// Compare to see if the addr is already registered
	// If it is not registered, we add it
	// If it is registered, we can set the data
	int clientId = -1;
	for (int i = 0; i < m_ConnectedClients.size(); i++)
	{
		ClientInfo& client = m_ConnectedClients[i];
		if (client.addr.sin_addr.s_addr == addr.sin_addr.s_addr
			&& client.addr.sin_port == addr.sin_port)
		{
			clientId = i;
			break;
		}
	}

	if (clientId == -1)
	{
		// Add the client
		ClientInfo newClient;
		newClient.addr = addr;
		newClient.addrLen = sizeof(addr);
		m_ConnectedClients.push_back(newClient);
		clientId = m_ConnectedClients.size() - 1;
	}

	ClientInfo& client = m_ConnectedClients[clientId];

	memcpy(&client.positionX, (const void*)&(buffer[0]), sizeof(int32_t));
	memcpy(&client.positionZ, (const void*)&(buffer[4]), sizeof(int32_t));
	memcpy(&client.directionX, (const void*)&(buffer[8]), sizeof(int8_t));
	memcpy(&client.directionZ, (const void*)&(buffer[9]), sizeof(int8_t));


	



	printf("From: %s:%d: {%d, %d}\n", inet_ntoa(client.addr.sin_addr), client.addr.sin_port, client.positionX, client.positionZ);
}

void NetworkServer::BroadcastUpdatesToClients()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	if (m_NextBroadcastTime > currentTime)
	{
		return;
	}

	printf("broadcast!\n");

	m_NextBroadcastTime = currentTime + std::chrono::milliseconds(100);

	// Add 20 ms to the next broadcast time from now()
	//m_NextBroadcastTime 

	const int length = 10 * 4;
	char data[length];


	PlayerData positions[4];

	int size = 10;

	for (int i = 0; i < m_ConnectedClients.size(); i++)
	{

		/*std::copy(&m_ConnectedClients[i].positionX, &m_ConnectedClients[i].positionX + 4, &data[i * sizeof(PlayerData)]);
		std::copy(&m_ConnectedClients[i].positionZ, &m_ConnectedClients[i].positionZ + 4, &data[i * sizeof(PlayerData) + 4]);
		std::copy(&m_ConnectedClients[i].directionX, &m_ConnectedClients[i].directionX + 1, &data[i * sizeof(PlayerData) + 8]);
		std::copy(&m_ConnectedClients[i].directionZ, &m_ConnectedClients[i].directionZ + 1, &data[i * sizeof(PlayerData) + 9]);*/


		memcpy(&data[i * size], &m_ConnectedClients[i].positionX, 4);
		memcpy(&data[i * size + 4], &m_ConnectedClients[i].positionZ, 4);
		memcpy(&data[i * size + 2 * 4], &m_ConnectedClients[i].directionX, 1);
		memcpy(&data[i * size + 2 * 4 + 1], &m_ConnectedClients[i].directionZ, 1);



		printf("%d", sizeof(data));

	}

	// Write
	for (int i = 0; i < m_ConnectedClients.size(); i++)
	{
		ClientInfo& client = m_ConnectedClients[i];
		int result = sendto(m_ListenSocket, &data[0], length, 0, (SOCKADDR*)&client.addr, client.addrLen);
		if (result == SOCKET_ERROR) {
			
			

			/*printf("send failed with error %d\n", WSAGetLastError());
			closesocket(m_ListenSocket);
			WSACleanup();*/
			return;
		}
	}
}
