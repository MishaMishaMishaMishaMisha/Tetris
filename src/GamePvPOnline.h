#pragma once
#include "GamePvPLocal.h"
#include "FieldSender.h"
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>


class GamePvPOnline : public GamePvPLocal
{
private:
	Field field_opponent; // ������ ����
	bool gameOver_player;
	bool gameOver_opponent;
	FieldSender sender;   // �������� � ��������� ��������� ����

	bool is_opponent_found;
	bool is_connected_to_server;
	bool is_error; // ���� �� ������� ����������� � ������� ��� ������� ������ ����� �������
	bool is_youReady;
	bool is_opponentReady;

	sf::Text text; // ���������� ���������
	sf::Text player1, player2; // ������� �� �����

	sf::TcpSocket socket;

	std::thread receiver_thread;

	uint32_t seed;

	sf::Clock clock;
	float time;

	void receiveMsg();
	void receiveData(std::string type, std::string data);

public:
	GamePvPOnline(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;
	void restart() override;
	GameScore getScore_right() override { return field_opponent.getScore(); }

	void disconnect();
};

