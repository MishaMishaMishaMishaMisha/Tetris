#include "Audio.h"

void Audio::load()
{
	file_manager.setPath("Files/");
	file_manager.setFileName("settings.txt");
	// загружаем настройки с файла
	loadSettings();
	

	if (!music.openFromFile(path + "main_music.ogg"))
	{
		throw std::exception("cannot open music file");
	}
	music.setLoop(true);
	music.setVolume(music_volume);

	buff_pause.loadFromFile(path + "pauseeffect.wav");
	sound_pause.setBuffer(buff_pause);
	sound_pause.setVolume(sound_volume);

	buff_fall_figure.loadFromFile(path + "zvuk-udara.wav");
	sound_fall_figure.setBuffer(buff_fall_figure);
	sound_fall_figure.setVolume(sound_volume);

	buff_destroy_row.loadFromFile(path + "hit_wall.wav");
	sound_destroy_row.setBuffer(buff_destroy_row);
	sound_destroy_row.setVolume(sound_volume);

	buff_gameover.loadFromFile(path + "gameover.wav");
	sound_gameover.setBuffer(buff_gameover);
	sound_gameover.setVolume(sound_volume);

	buff_newrecord.loadFromFile(path + "newrecord.wav");
	sound_newrecord.setBuffer(buff_newrecord);
	sound_newrecord.setVolume(sound_volume);

	buff_select.loadFromFile(path + "select.wav");
	sound_select.setBuffer(buff_select);
	sound_select.setVolume(sound_volume);


}

void Audio::playMusic()
{
	music.play();
	isPlaying = true;
}

void Audio::stopMusic()
{
	music.stop();
	isPlaying = false;
}

void Audio::pauseMusic(bool isPause)
{
	if (isPause)
	{
		music.pause();
		isPlaying = false;
	}
	else
	{
		playMusic();
		isPlaying = true;
	}
}

void Audio::playPauseEffect()
{
	sound_pause.play();
}

void Audio::playFallFigureEffect()
{
	sound_fall_figure.play();
}

void Audio::playDestroyRowEffect()
{
	sound_destroy_row.play();
}

void Audio::playGameoverEffect()
{
	sound_gameover.play();
}

void Audio::playNewRecordEffect()
{
	sound_newrecord.play();
}

void Audio::playSelectEffect()
{
	sound_select.play();
}

void Audio::loadSettings()
{
	std::string line = file_manager.readLine(); // читаем строку
	std::vector<unsigned int> numbers = file_manager.splitIntoNumbers(line); // переводим в числа

	if (numbers.size() >= 2)
	{
		music_volume = numbers[0];
		sound_volume = numbers[1];
	}
}

void Audio::saveSettings()
{
	std::string line = std::to_string(music_volume) + " " + std::to_string(sound_volume);
	file_manager.writeLine(line);
}

void Audio::setMusicVolume(uint8_t vol)
{
	if (vol == music_volume) return;
	music_volume = vol;
	music.setVolume(music_volume);
}
void Audio::setSoundVolume(uint8_t vol)
{
	if (vol == sound_volume) return;
	sound_volume = vol;
	sound_destroy_row.setVolume(sound_volume);
	sound_fall_figure.setVolume(sound_volume);
	sound_gameover.setVolume(sound_volume);
	sound_newrecord.setVolume(sound_volume);
	sound_pause.setVolume(sound_volume);
	sound_select.setVolume(sound_volume);
}