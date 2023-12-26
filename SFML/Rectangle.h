#pragma once

#include "libs.h"

class Rectangle {
public:
	Rectangle();
	Rectangle(sf::Vector2f, sf::Vector2f);
	void draw_to(sf::RenderWindow&);
	void move();
	void moveA();
	void moveA_main();
	void moveD();
	void moveD_main();
	void move_fire(int);
	void move_enemy(int);
	void setPosition(int, int);
	void setSize(sf::Vector2f);
	void fire(Rectangle**, int);
	void setEnemy();
	void setColor(sf::Color);
	void setColor();

	friend void fill(Rectangle*, int);
	friend void print_obj(sf::RenderWindow&, Rectangle*, int);
	friend void print_enemies(sf::RenderWindow&, Rectangle*, int, int);
	friend void print_fire(sf::RenderWindow&, Rectangle*, int, int);
	friend int check_rect_enemy(Rectangle&, Rectangle*, int);
	friend void check_killed(Rectangle*, int, Rectangle*, int, int*, int*, int);
private:
	sf::RectangleShape rect;
	int enemy_down;
	int width_to_avoid;
	int height_to_avoid;
	bool max_width = false;
	bool max_height = false;
};

void fill(Rectangle*, int);
void print_obj(sf::RenderWindow&, Rectangle*, int);
void print_enemies(sf::RenderWindow&, Rectangle*, int, int);
void print_fire(sf::RenderWindow&, Rectangle*, int, int);
void check_killed(Rectangle*, int, Rectangle*, int, int*, int*, int);
int check_rect_enemy(Rectangle&, Rectangle*, int);
void change_str(std::string&);
void fill_highscore(string**, int**, int, string, int);
void sort_highscore(string**, int**, int);
void clear_memory(Rectangle**);
void clear_memory(int**);
void clear_memory(string**);