#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <array>
#include <SFML/Network.hpp>
#include <mariadb/mysql.h>
#include <iomanip>
#include <sstream>


class DataBase
{
private:
	MYSQL* conn;

	std::vector<std::shared_ptr<sf::TcpSocket>> connections;
	size_t counter = 0;

	std::mutex connections_mutex;
	std::mutex db_mutex; // mutex для доступа к базе

	sf::TcpListener listener;

	std::vector<std::thread> threads;

	sf::IpAddress serverIP;
	uint16_t port;

	void playerHandler(int index); // обработка каждого игрока

	// защита от одновременного использования вектора connections:
	void addConnection(std::shared_ptr<sf::TcpSocket> client);
	std::shared_ptr<sf::TcpSocket> getConnection(size_t index);
	void resetConnection(size_t index);

	// запросы в бд
	void checkUserInDB(size_t user_index, std::string name, std::string pass); // если ли игрок с таким именем и паролем в бд
	void addNewUser(size_t user_index, std::string name, std::string password); // добавить нового игрока в бд
	void updateRecord(size_t user_index, std::string name, std::array<uint32_t, 5> record); // Обновить рекорд пользователя
	void downloadRecord(size_t user_index, std::string name); // скачать рекорд пользователя из бд
	void downloadUserRating(size_t user_index, std::string name); // скачать рейтинг игрока
	void downloadTop5(size_t user_index); // скачать топ 5 игроков
	
	// создать строку для таблицы рейтинга
	std::string formatPlayerRow(
    size_t place,
    const std::string& username,
    const std::string& score,
    const std::string& lines,
    const std::string& level,
    const std::string& pvp_games,
    const std::string& pvp_wins);

public:
	DataBase(sf::IpAddress ip, uint16_t port) : serverIP(ip), port(port), conn(nullptr) {}

	void init_db();
	void run();

};




