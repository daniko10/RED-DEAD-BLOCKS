#include "Rectangle.h"

#include "libs.h"


Rectangle::Rectangle() {
	rect.setPosition({ -100,-100 });
	width_to_avoid = -100;
	height_to_avoid = -100;
}

Rectangle::Rectangle(sf::Vector2f rect_size, sf::Vector2f pos) {
	rect.setSize(rect_size);
	rect.setPosition(pos);

	width_to_avoid = pos.x;
	height_to_avoid = pos.y;
}

void Rectangle::draw_to(sf::RenderWindow& window) {
	window.draw(rect);
}

void Rectangle::move() {

	max_width = width_to_avoid >= 1230 ? true : width_to_avoid <= 410 ? false : max_width;
	max_height = height_to_avoid >= 670 ? true : height_to_avoid <= 0 ? false : max_height;

	width_to_avoid = max_width == true ? width_to_avoid -= 3 : width_to_avoid += 3;
	height_to_avoid = max_height == true ? height_to_avoid -= 3 : height_to_avoid += 3;

	if (width_to_avoid >= 1230 || width_to_avoid <= 410 || height_to_avoid >= 670 || height_to_avoid <= 0)
		setColor();

	rect.setPosition(width_to_avoid, height_to_avoid);

}
void Rectangle::moveA() {
	
	max_width = width_to_avoid <= 0 ? true : false;
	width_to_avoid = max_width == false ? width_to_avoid -= 5 : width_to_avoid;

	rect.setPosition(width_to_avoid, height_to_avoid);

}

void Rectangle::moveA_main() {

	max_width = width_to_avoid <= 410 ? true : false;
	width_to_avoid = max_width == false ? width_to_avoid -= 5 : width_to_avoid;

	rect.setPosition(width_to_avoid, height_to_avoid);

}

void Rectangle::moveD() {

	max_width = width_to_avoid >= 350 ? true : false;
	width_to_avoid = max_width == false ? width_to_avoid += 5 : width_to_avoid;

	rect.setPosition(width_to_avoid, height_to_avoid);

}

void Rectangle::moveD_main() {

	max_width = width_to_avoid >= 1230 ? true : false;
	width_to_avoid = max_width == false ? width_to_avoid += 5 : width_to_avoid;

	rect.setPosition(width_to_avoid, height_to_avoid);

}

void Rectangle::move_fire(int var) {

	max_height = var == 0 ? height_to_avoid <= 400 ? true : false : height_to_avoid <= 20 ? true : false;
	height_to_avoid = max_height == false ? height_to_avoid-=2 : height_to_avoid = -10;

	rect.setPosition(width_to_avoid, height_to_avoid);
}

void Rectangle::move_enemy(int var) {
	max_height = height_to_avoid >= 640 ? true : false;
	height_to_avoid = max_height == false ? height_to_avoid += enemy_down : var == 0 ? height_to_avoid = 370 : height_to_avoid = 20;

	rect.setPosition(width_to_avoid, height_to_avoid);
}

void Rectangle::fire(Rectangle** ptr, int size) {
	Rectangle* temp_ptr = new Rectangle[size];
	temp_ptr[size - 1].setColor(sf::Color::Yellow);
	temp_ptr[size - 1].setPosition(width_to_avoid + 25, 620);
	temp_ptr[size - 1].setSize({ 10, 10 });

	if (*ptr) {
		for (int i = 0; i < size - 1; i++) {
			temp_ptr[i] = (*ptr)[i];
		}
		delete [] *ptr;
	}

	*ptr = temp_ptr;
}

void Rectangle::setPosition(int x, int y) {
	sf::Vector2f pos(x, y);
	rect.setPosition(pos);
	width_to_avoid = pos.x;
	height_to_avoid = pos.y;
}


void Rectangle::setSize(sf::Vector2f size) {
	rect.setSize(size);
}

void Rectangle::setEnemy() {
	enemy_down = rand() % 2 + 1;
}

void Rectangle::setColor(sf::Color color) {
	rect.setFillColor(color);
}

void Rectangle::setColor() {
	rect.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

void fill(Rectangle* ptr, int size) {
	srand(time(nullptr));
	
	int y = rand() % 100;
	ptr[0].setPosition(1230, y);
	ptr[0].setSize({ 50, 50 });
	ptr[0].setColor();

	for (int i = 1; i < size/2; i++) {
		y += 60;
		ptr[i].setSize({ 50, 50 });
		ptr[i].setPosition(1230, y);
		ptr[i].setColor();
	}

	y = ptr[0].height_to_avoid;

	for (int i = size/2 ; i < size; i++) {
		ptr[i].setSize({ 50, 50 });
		ptr[i].setPosition(410, y);
		ptr[i].setColor();

		y += 60;

	}

}

void print_obj(sf::RenderWindow& window, Rectangle* rect, int size) {
	for (int i = 0; i < size; i++) {
		rect[i].draw_to(window);
		rect[i].move();
	}
}

void print_enemies(sf::RenderWindow& window, Rectangle* enemy, int size, int var) {
	for (int i = 0; i < size; i++) {
		if (var == 0) {
			if (enemy[i].height_to_avoid >= 420)
				enemy[i].draw_to(window);
			enemy[i].move_enemy(0);
		}
		else {
			enemy[i].draw_to(window);
			enemy[i].move_enemy(1);
		}
		
	}
}

void print_fire(sf::RenderWindow& window, Rectangle* ptr, int size, int var) {
	for (int i = 0; i < size; i++) {
		ptr[i].draw_to(window);
		ptr[i].move_fire(var);
	}
}

void check_bonus(Rectangle* balls, int balls_size, Rectangle* bonus, int n, int* score) {
	for (int i = 0; i < balls_size; i++) {
		if (balls[i].width_to_avoid > bonus->width_to_avoid) {
			if ((balls[i].height_to_avoid - bonus->height_to_avoid < 20 && balls[i].height_to_avoid - bonus->height_to_avoid > -20) && balls[i].width_to_avoid - bonus->width_to_avoid < 20 && balls[i].width_to_avoid - bonus->width_to_avoid > -20) {
				bonus->enemy_down = rand() % 10 + 1;
				bonus->setPosition(rand()%820 + 410, 0);
				*score += 10;
				balls[i].max_height = true;
				balls[i].height_to_avoid = -10;
				balls[i].width_to_avoid = 410;
				balls[i + 1].max_height = true;
				balls[i + 1].height_to_avoid = -10;
				balls[i + 1].width_to_avoid = 410;
				return;
			}
		}
		else {
			if ((balls[i].height_to_avoid - bonus->height_to_avoid < 10 && balls[i].height_to_avoid - bonus->height_to_avoid > -10) && balls[i].width_to_avoid - bonus->width_to_avoid < 10 && balls[i].width_to_avoid - bonus->width_to_avoid > -10) {
				bonus->setPosition(rand() % 820 + 410, 0);
				*score += 10;
				balls[i].max_height = true;
				balls[i].height_to_avoid = -10;
				balls[i].width_to_avoid = 410;
				balls[i + 1].max_height = true;
				balls[i + 1].height_to_avoid = -10;
				balls[i + 1].width_to_avoid = 410;
				return;
			}
		}
	}
}

void check_killed(Rectangle* balls, int size1, Rectangle* rects, int size2, int *SCORE, int *LOST, int var) {
	for (int j = 0; j < size2; j++)
		if (rects[j].height_to_avoid >= 640)
			(*LOST)++;
	
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {

			if ((balls[i].width_to_avoid - rects[j].width_to_avoid <= 20 && balls[i].width_to_avoid - rects[j].width_to_avoid >= -20) && (balls[i].height_to_avoid - rects[j].height_to_avoid <= 20 && balls[i].height_to_avoid - rects[j].height_to_avoid >= -20)) {
				if(var != 1)
					rects[j].height_to_avoid = 370;
				else
					rects[j].height_to_avoid = 20;

				balls[i].max_height = true;
				balls[i].height_to_avoid = -10;
				balls[i].width_to_avoid = 410;
				balls[i + 1].max_height = true;
				balls[i + 1].height_to_avoid = -10;
				balls[i + 1].width_to_avoid = 410;
				
				(*SCORE)++;
				return;
			}
		}
	}
}

int check_rect_enemy(Rectangle& rect, Rectangle* enemies, int size) {
	for (int i = 0; i < size;i++) {
		if ((enemies[i].width_to_avoid - rect.width_to_avoid <= 30 && enemies[i].width_to_avoid - rect.width_to_avoid >= -30) && (enemies[i].height_to_avoid - rect.height_to_avoid <= 30 && enemies[i].height_to_avoid - rect.height_to_avoid >= -30))
			return 1;
	}
	return 0;
}

void change_str(std::string& ptr) {
	const int size = ptr.length();
	ptr[size - 1] = '\0';
	ptr.resize(size - 1);
}

void fill_highscore(string** tab_str, int** tab_int, int size, string temp_str, int temp_int) {
	string* t = new string[size];
	int* t_i = new int[size];

	t[size - 1] = temp_str;
	t_i[size - 1] = temp_int;

	for (int i = 0;i < size - 1; i++) {
		t[i] = (*tab_str)[i];
		t_i[i] = (*tab_int)[i];
	}

	if (*tab_str != nullptr && *tab_int != nullptr) {
		delete[] *tab_str;
		delete[] *tab_int;
	}

	*tab_str = t;
	*tab_int = t_i;
}

void sort_highscore(string** _str, int** _int, int size) {
	string temp_s = "";
	int temp_i;

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if ((*_int)[i] < (*_int)[j]) {
					
					temp_i = (*_int)[i];
					(*_int)[i] = (*_int)[j];
					(*_int)[j] = temp_i;
					
					temp_s = (*_str)[i];
					(*_str)[i] = (*_str)[j];
					(*_str)[j] = temp_s;
				}
			}
	}
}

void clear_memory(Rectangle** ptr) {
	if(*ptr)
		delete[] * ptr;
}

void clear_memory(int** ptr) {
	if(*ptr)
		delete[] * ptr;
}

void clear_memory(string** ptr) {
	if(*ptr)
		delete[] * ptr;
}