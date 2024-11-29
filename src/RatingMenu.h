#pragma once
#include "BaseWindow.h"
#include "InputText.h"
#include <functional> // std::hash
#include <SFML/Network.hpp>

class RatingMenu : public BaseWindow
{
private:
	ServerInfo serverInfo;
	sf::Packet packet;
	sf::TcpSocket socket;
	sf::IpAddress db_IP;
	uint16_t db_port;
	bool is_connected;
	bool is_error_connetion;
	void connect();
	void disconnect();

	// ������ ������� �� ��������
	const uint8_t max_size_rating_list = 10;
	uint16_t current_size_rating_list = 10;
	uint8_t max_size_table = 10;
	std::vector<sf::Text> players;
	std::vector<sf::Text> players_table;
	void createPlayersTable();
	void resetListColor();

	sf::Font& font;
	sf::Text title; // �������� ����
	sf::Text error; // ����� ������ ��� �����
	sf::Text username; // ��� ������
	std::string password_hash;

	// ���� ��� ����� ������
	InputText input_name;
	InputText input_password;
	InputText input_confirm_password;
	std::hash<std::string> hash_fn;

	// ����� ���� ������� (���� ����� �� ����� � ���)
	bool is_main;
	bool is_register;
	bool is_login;

	bool is_logged_in; // ����� �� ������������ � �������

	FileManager file_user;
	FileManager file_record;

	// �-�� ������ � ������ �� ����
	uint8_t num_buttons_main;
	uint8_t num_buttons_register;
	uint8_t num_buttons_login;
	uint8_t num_buttons_rating;
	// ������ ������� ����
	std::vector<sf::Text> buttons_main;
	std::vector<sf::Text> buttons_register;
	std::vector<sf::Text> buttons_login;
	std::vector<sf::Text> buttons_rating;
	// �������� ������ ������� ����
	std::vector<std::string> names_main; 
	std::vector<std::string> names_register;
	std::vector<std::string> names_login;
	std::vector<std::string> names_rating;
	// �������� ������
	int8_t selected_button = 0;

	void highlightButton(); // �������� ��������� ������ ������ ������
	void resetButtonsColor(); // ������� �������� �����

	void setTitle(std::string text); // ���������� ����� ���������

	bool checkInput(); // ��������� ������������ ������

	void moveUp(); // ����������� �� ������ ����
	void moveDown(); // ����������� �� ������ ����

	void showRatingList();

	void resetRecordFile(); // �������� ���� record.bin
	bool checkIsNewRecord(); // ��������� ���� �� ���������� ����� ������ ��� ������� ����� pvp ����
	void setRecordOld(); // ������� ���� � �������� "������" (�� ���� ������ ������� ����������� �� ����)

	// �������������� � ��
	bool addNewUserToDB(std::string name, std::string password); // �������� ������ ������ � �� (���� �� ���� ���������� ���)
	void uploadRecordToDB(); // ��������� ������ �� ����� � ��
	void downloadRecordFromDB(); // ������� ������ �� �� � �������� � ����
	bool isUserInDB(std::string name, std::string pass); // ���� �� ����� � ������ ������� � ����
	void downloadRating(bool isTop = true); // ������� �������: ��� ������� ���� ����� ������

	bool sendPacket();
	bool receivePacket();

public:
	RatingMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;



};

