#ifndef _STATS_H_
#define _STATS_H_

#include <cstdint>
#include <iostream>

struct Stats
{
	Stats() : 
		expected_packets_sent(0), expected_packets_received(0), 
		packets_sent(0), packets_received(0), 
		bytes_sent(0), bytes_received(0), 
		send_socket_error_count(0), received_socket_error_count(0),
		elapsed_seconds(0)
	{}

	void PrintStats()
	{
		using namespace std;

		cout << "Elapsed time: " << elapsed_seconds << " seconds" << endl << endl;

		cout << "Packets sent: " << packets_sent << "(" << (expected_packets_sent ? 100.0*packets_sent / expected_packets_sent : 0) << "%)" << endl;
		cout << "Bytes sent: " << bytes_sent << " bytes or " << bytes_sent / (1024.0 * 1024.0) << " MB" << endl;
		cout << "Error count: " << send_socket_error_count << endl;
		cout << "Throughput:" << endl;
		cout << "\t" << packets_sent / elapsed_seconds << " packets/s" << endl;
		cout << "\t" << bytes_sent / elapsed_seconds << " bytes/s" << endl;
		cout << "\t" << bytes_sent / (1024 * 1024 * elapsed_seconds) << " MB/s" << endl;
		cout << "\t" << 8*bytes_sent / (1024 * 1024 * elapsed_seconds) << " Mbps" << endl;
		cout << endl << endl;

		cout << "Packets received: " << packets_received << "(" << (expected_packets_received ? 100.0*packets_received / expected_packets_received : 0) << "%)" << endl;
		cout << "Bytes received: " << bytes_received << " bytes or " << bytes_received / (1024.0 * 1024.0) << " MB" << endl;
		cout << "Error count: " << received_socket_error_count << endl;
		cout << "Throughput:" << endl;
		cout << "\t" << packets_received / elapsed_seconds << " packets/s" << endl;
		cout << "\t" << bytes_received / elapsed_seconds << " bytes/s" << endl;
		cout << "\t" << bytes_received / (1024 * 1024 * elapsed_seconds) << " MB/s" << endl;
		cout << "\t" << 8 * bytes_received / (1024 * 1024 * elapsed_seconds) << " Mbps" << endl;
	}

	uint64_t expected_packets_sent;
	uint64_t expected_packets_received;

	uint64_t packets_sent;
	uint64_t packets_received;

	uint64_t bytes_sent;
	uint64_t bytes_received;

	int send_socket_error_count;
	int received_socket_error_count;

	double elapsed_seconds;
};


#endif