#include "InputText.h"

InputText::InputText(sf::Font& font) :
	is_invisible(false),
	font(font)

{
	// поле для ввода и текст по умолч.

	input_field.setSize(sf::Vector2f(400, 50));
	input_field.setPosition(200, 200);
	input_field.setFillColor(sf::Color::White);
	input_field.setOutlineThickness(2);
	input_field.setOutlineColor(sf::Color::Black);

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(input_field.getPosition().x + 10, input_field.getPosition().y + 10);

}

void InputText::draw(sf::RenderWindow& win)
{
	win.draw(input_field);
	win.draw(text);
}

void InputText::setInvisible(bool inv)
{
	is_invisible = inv;
}

std::string InputText::getStr()
{
	return str;
}

void InputText::inputButton(sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b')
		{
			// Backspace
			if (!str.empty())
			{
				str.pop_back();
				inv_str.pop_back();
			}
		}
		else if (event.text.unicode == '\r')
		{
			// Enter
			// Обработка завершения ввода (например, отправка текста)

		}
		else if (event.text.unicode < 128)
		{
			if (str.length() <= max_input_text_size)
			{
				// ASCII символы
				str += static_cast<char>(event.text.unicode);
				inv_str += '*';
			}
		}

		if (is_invisible)
		{
			text.setString(inv_str);
		}
		else
		{
			text.setString(str);
		}

	}

}

void InputText::setPosition(float x, float y)
{
	input_field.setPosition(x, y);
	text.setPosition(input_field.getPosition().x + 10, input_field.getPosition().y + 10);
}

void InputText::setSize(sf::Vector2f size)
{
	input_field.setSize(size);
}

void InputText::setTextSize(size_t size)
{
	text.setCharacterSize(size);
}

void InputText::reset()
{
	str.clear();
	inv_str.clear();
	text.setString("");
}