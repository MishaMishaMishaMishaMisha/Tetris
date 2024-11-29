#pragma once
#include "GamePvPLocal.h"
#include "FieldSender.h"
#include "FileManager.h"
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>


class GamePvPOnline : public GamePvPLocal
{
private:
	ServerInfo serverInfo;

	bool is_logged_in;
	std::string player_name = "";
	std::string opponent_name = "";
	FileManager file_user;
	FileManager file_record;
	void checkIsLoggedIn();
	void increaseGamesCount();
	void increaseWinsCount();

	Field field_opponent; // правое поле
	bool gameOver_player;
	bool gameOver_opponent;
	FieldSender sender;   // отправка и получение состояния поля
	sf::Packet send_packet;

	bool is_opponent_found;
	bool is_connected_to_server;
	bool is_error; // если не удается подключится к серверу или слишком долгий поиск игроков
	bool is_youReady;
	bool is_opponentReady;

	sf::Text text; // полученные сообщения
	sf::Text player1, player2; // надписи по углам

	sf::TcpSocket socket;
	sf::IpAddress serverIP;
	uint16_t port; // порт сервера для tcp передачи
	uint16_t upd_port; // порт сервера для udp передачи

	std::thread receiver_thread;
	void receiveMsg();
	void receiveData(std::string type, std::string data);

	uint32_t seed;

	sf::Clock clock;
	float time;

	// ping
	///////
	sf::UdpSocket ping_socket;
	bool is_binded;
	std::thread ping_thread;
	sf::Packet ping_packet;

	//sf::UdpSocket ping_socket_receiver;
	//bool is_receiver_binded;
	//std::thread ping_thread_receiver;
	//sf::Packet ping_packet_receiver;

	sf::Text ping_text;
	sf::Clock ping_clock;
	float ping_time;

	void checkPing();
	///////


	void drawText(); // отобразить текст сообщения по центру
	bool is_textChanged;

	bool connectToServer();

public:
	GamePvPOnline(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;
	void restart() override;
	GameScore getScore_right() override { return field_opponent.getScore(); }

	void disconnect();

	std::pair<std::string, std::string> getNames();
};

