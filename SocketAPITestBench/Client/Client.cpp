#include <iostream>

#include "Common/PerfCounter.h"
#include "Common/Stats.h"

#include<winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

void PrintUsage()
{
	cout << "Usage: client <server_ip_address> <port> <packet_count> <packet_size>" << endl;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		PrintUsage();
		exit(EXIT_FAILURE);
	}

	char* ip = argv[1];
	int port = atoi(argv[2]);
	unsigned int packet_count = atoi(argv[3]);
	unsigned int packet_size = atoi(argv[4]);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cerr << "Failed. Error Code : "<< WSAGetLastError() << endl;
		return 1;
	}

	SOCKET s;
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		cerr << "Could not create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	struct sockaddr_in server;
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	if (inet_pton(server.sin_family, ip, &server.sin_addr) != 1)
	{
		cerr << "inet_pton failed " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	server.sin_port = htons(port);

	Stats stats;
	stats.expected_packets_sent = packet_count;

	// Send some data !!!
	char* buffer = new char[packet_size];

	PerfCounter p;
	p.Start();

	for (unsigned int i = 0; i < packet_count; ++i)
	{
		int res = sendto(s, buffer, packet_size, 0, (struct sockaddr*)&server, sizeof(server));
		if (res == 0)
		{
			stats.send_socket_error_count++;
		}
		else
		{
			stats.packets_sent++;
			stats.bytes_sent += res;
		}
	}

	p.Stop();

	stats.elapsed_seconds = p.GetElapsedSec();

	stats.PrintStats();

	closesocket(s);
	WSACleanup();

	return 0;
}