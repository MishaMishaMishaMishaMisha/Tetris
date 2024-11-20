#pragma once
#include <SFML/Audio.hpp>
#include "FileManager.h"

// ����� ��� ������ �� ������
class Audio
{
private:
	std::string path = "Sounds/"; // ���� � ������ � ������
	sf::Music music; // ������ �� ����� ����

	sf::Sound sound_pause; // �������� ������ - �����
	sf::SoundBuffer buff_pause;

	sf::Sound sound_fall_figure; // �������� ������ - ������� ������
	sf::SoundBuffer buff_fall_figure;

	sf::Sound sound_destroy_row; // �������� ������ - ���������� ����
	sf::SoundBuffer buff_destroy_row;

	sf::Sound sound_gameover; // �������� ������ - ����� ���� (��� �������)
	sf::SoundBuffer buff_gameover;

	sf::Sound sound_newrecord; // �������� ������ - ����� ���� (����� �������)
	sf::SoundBuffer buff_newrecord;

	sf::Sound sound_select; // �������� ������ - ����� ������ ����
	sf::SoundBuffer buff_select;

	uint8_t sound_volume = 20; // ��������� ������
	uint8_t music_volume = 30; // ��������� ������
	bool isPlaying = false; // ������ �� ������

	FileManager file_manager;

public:
	Audio() = default;
	void load(); // �������� ������ � ������
	void playMusic(); // �������� ������
	void stopMusic(); // ��������� ������
	void pauseMusic(bool isPause); // ��������� �� ����� ������
	// ��������� �������� ��������
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

	void loadSettings(); // ��������� ��������� ��������� � �����
	void saveSettings(); // �������� ��������� ��������� � ����

	bool get_isPlaying() { return isPlaying; }
};

