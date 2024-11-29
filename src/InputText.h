#pragma once
#include <SFML/Graphics.hpp>

class InputText
{
private:
	std::string str;
	std::string inv_str; // ��������� ����� (*)
	sf::Text text;
	sf::Font& font;
	sf::RectangleShape input_field;
	bool is_invisible; // ��������� ����� (��� ������)
	const size_t max_input_text_size = 20;

public:
	InputText(sf::Font& font);

	void draw(sf::RenderWindow& win);
	void setInvisible(bool inv);
	std::string getStr();
	void inputButton(sf::Event& event);
	void setPosition(float x, float y);
	void setSize(sf::Vector2f size);
	void setTextSize(size_t size);
	void reset();

	
};

