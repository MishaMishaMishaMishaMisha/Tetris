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

	// список игроков из рейтинга
	const uint8_t max_size_rating_list = 10;
	uint16_t current_size_rating_list = 10;
	uint8_t max_size_table = 10;
	std::vector<sf::Text> players;
	std::vector<sf::Text> players_table;
	void createPlayersTable();
	void resetListColor();

	sf::Font& font;
	sf::Text title; // название меню
	sf::Text error; // текст ошибки при вводе
	sf::Text username; // имя игрока
	std::string password_hash;

	// поля для ввода текста
	InputText input_name;
	InputText input_password;
	InputText input_confirm_password;
	std::hash<std::string> hash_fn;

	// какое меню открыто (если игрок не вошел в акк)
	bool is_main;
	bool is_register;
	bool is_login;

	bool is_logged_in; // зашел ли пользователь в аккаунт

	FileManager file_user;
	FileManager file_record;

	// к-во кнопок в каждом из меню
	uint8_t num_buttons_main;
	uint8_t num_buttons_register;
	uint8_t num_buttons_login;
	uint8_t num_buttons_rating;
	// кнопки каждого меню
	std::vector<sf::Text> buttons_main;
	std::vector<sf::Text> buttons_register;
	std::vector<sf::Text> buttons_login;
	std::vector<sf::Text> buttons_rating;
	// названия кнопок каждого меню
	std::vector<std::string> names_main; 
	std::vector<std::string> names_register;
	std::vector<std::string> names_login;
	std::vector<std::string> names_rating;
	// выбрання кнопка
	int8_t selected_button = 0;

	void highlightButton(); // выделить выбранную кнопку другим цветом
	void resetButtonsColor(); // вернуть исходные цвета

	void setTitle(std::string text); // установить текст заголовка

	bool checkInput(); // проверить правильность текста

	void moveUp(); // переключить на кнопку выше
	void moveDown(); // переключить на кнопку ниже

	void showRatingList();

	void resetRecordFile(); // обнулить файл record.bin
	bool checkIsNewRecord(); // проверить были ли установлен новый рекорд или сыграны новые pvp игры
	void setRecordOld(); // сделать файл с рекордом "старым" (то есть нового рекорда установлене не было)

	// взаимодействие с бд
	bool addNewUserToDB(std::string name, std::string password); // добавить нового игрока в бд (если он ввел уникальное имя)
	void uploadRecordToDB(); // загрузить рекорд из файла в бд
	void downloadRecordFromDB(); // скачать рекорд из бд и записать в файл
	bool isUserInDB(std::string name, std::string pass); // есть ли игрок с такими данными в базе
	void downloadRating(bool isTop = true); // скачать рейтинг: топ игроков либо место игрока

	bool sendPacket();
	bool receivePacket();

public:
	RatingMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite);

	void draw() override;
	void handleEvents(sf::Event& event) override;
	GameState getNextState() override;
	void set_Active() override;



};

