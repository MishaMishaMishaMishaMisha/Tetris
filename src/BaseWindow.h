#pragma once
#include "Controls.h"
#include "Globals.h"
#include "Audio.h"

// ������� ��������� ���� ����
class BaseWindow
{
protected:
	bool isActive = false; // ���� - �������� ���� ��� ���
	Controls controls;
	Audio& audio;
	sf::Sprite& backgroundSprite; // ���
	sf::RenderWindow& window;

public:
	BaseWindow(Audio& a, sf::Sprite& bs, sf::RenderWindow& win) : audio(a), backgroundSprite(bs), window(win) {};

	virtual void draw() = 0; // ����� �� �����
	virtual void handleEvents(sf::Event& event) = 0; // ��������� �������
	virtual void set_Active() { isActive = true; }
	virtual GameState getNextState() = 0; // ����� ���� ����� ������� �� �������� ����

	bool get_isActive() const { return isActive; }
};

