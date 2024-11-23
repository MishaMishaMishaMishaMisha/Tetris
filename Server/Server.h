#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <SFML/Network.hpp>

class Server
{
private:
	std::vector<std::shared_ptr<sf::TcpSocket>> connections;
	size_t counter = 0;

	std::map<int, int> pairs; // Хранит пары клиентов (client1 -> client2) для tcp передачи

	std::unordered_map<int, sf::IpAddress> udpIPs;    // Карта: ID игрока -> IP-адрес для udp передачи
	std::unordered_map<int, uint16_t> udpPorts; // Карта: ID игрока -> порт для udp передачи

	sf::UdpSocket udp_socket;


	std::mutex connections_mutex;
	std::mutex connections_upd_mutex;
	std::mutex pairs_mutex;

	sf::TcpListener listener;

	std::vector<std::thread> threads;
	std::thread udp_thread;

	sf::Packet packet_main;

	sf::IpAddress serverIP;
	uint16_t port;
	uint16_t port_udp;

	void playerHandler(int index); // обработка каждого игрока
	void udpPlayerHandler(); // обработка клиентов по UDP socket

	// защита от одновременного использования вектора connections:
	void addConnection(std::shared_ptr<sf::TcpSocket> client);
	std::shared_ptr<sf::TcpSocket> getConnection(size_t index);
	void resetConnection(size_t index);

	// защита от одновременного использования pairs:
	void addPair(size_t index, int value);
	int getPair(size_t index);

public:
	Server(sf::IpAddress ip, uint16_t port, uint16_t port_udp) : serverIP(ip), port(port), port_udp(port_udp) {}

	void init_server();
	void run();

};

