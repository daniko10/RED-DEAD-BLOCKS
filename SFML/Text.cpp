#include "Text.h"

Text_class::Text_class(sf::Font& font, int char_size, string str, int x, int y) {
	text.setFont(font);
	text.setCharacterSize(char_size);
	text.setString(str);
	
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;

	text.setPosition(pos);
}

void Text_class::setCharacter(int char_size) {
	text.setCharacterSize(char_size);
}

void Text_class::setString(string str) {
	text.setString(str);
}

void Text_class::setPosition(int x, int y) {
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;

	text.setPosition(pos);
}

void Text_class::setFont(sf::Font& font) {
	text.setFont(font);
}

void Text_class::draw_to(sf::RenderWindow& window) {
	window.draw(text);
}

void Text_class::setStyle(sf::Text::Style choice) {
	text.setStyle(choice);
}

void Text_class::setFillColor(sf::Color col) {
	text.setFillColor(col);
}

void clear_memory(Text_class** ptr) {
	if (*ptr) {
		delete * ptr;
		*ptr = nullptr;
	}
}