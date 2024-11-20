#pragma once
#include <SFML/Audio.hpp>
#include "FileManager.h"

// класс для работы со звуком
class Audio
{
private:
	std::string path = "Sounds/"; // путь к звукам и музыке
	sf::Music music; // музыка во время игры

	sf::Sound sound_pause; // звуковой эффект - пауза
	sf::SoundBuffer buff_pause;

	sf::Sound sound_fall_figure; // звуковой эффект - падение фигуры
	sf::SoundBuffer buff_fall_figure;

	sf::Sound sound_destroy_row; // звуковой эффект - разрушение ряда
	sf::SoundBuffer buff_destroy_row;

	sf::Sound sound_gameover; // звуковой эффект - конец игры (без рекорда)
	sf::SoundBuffer buff_gameover;

	sf::Sound sound_newrecord; // звуковой эффект - конец игры (новый рекорда)
	sf::SoundBuffer buff_newrecord;

	sf::Sound sound_select; // звуковой эффект - выбор пункта меню
	sf::SoundBuffer buff_select;

	uint8_t sound_volume = 20; // громкость звуков
	uint8_t music_volume = 30; // грумкость музыки
	bool isPlaying = false; // играет ли музыка

	FileManager file_manager;

public:
	Audio() = default;
	void load(); // загрузка звуков и музыки
	void playMusic(); // включить музыку
	void stopMusic(); // выключить музыку
	void pauseMusic(bool isPause); // поставить на паузу музыку
	// включение звуковых эффектов
	void playPauseEffect();
	void playFallFigureEffect();
	void playDestroyRowEffect();
	void playGameoverEffect();
	void playNewRecordEffect();
	void playSelectEffect();

	uint8_t getMusicVolume() { return music_volume; }
	uint8_t getSoundVolume() { return sound_volume; }

	void setMusicVolume(uint8_t vol);
	void setSoundVolume(uint8_t vol);

	void loadSettings(); // загрузить настройки громкости с файла
	void saveSettings(); // схранить настройки громкости в файл

	bool get_isPlaying() { return isPlaying; }
};

