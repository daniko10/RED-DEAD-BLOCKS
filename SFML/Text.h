#pragma once

#include "libs.h"
#include <SFML\Graphics.hpp>

class Text_class {
public :
	Text_class(sf::Font&, int, string, int, int);
	void setCharacter(int);
	void setString(string);
	void setPosition(int, int);
	void setFont(sf::Font&);
	void draw_to(sf::RenderWindow&);
	void setStyle(sf::Text::Style);
	void setFillColor(sf::Color);

private:
	sf::Text text;
};

void clear_memory(Text_class**);