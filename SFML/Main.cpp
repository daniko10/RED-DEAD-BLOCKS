#include "libs.h"
#include "Rectangle.h"
#include "Text.h"

int main() {
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode(1280, 720), "GAME");
	window.setFramerateLimit(60);

	///////////////////////////////// INTRO 

	int SCORE = 0;
	int LOST = 0;
	int START = 0;
	bool STOPPED_SHOWING = false;

	Rectangle* rect_enemies = new Rectangle[5];
	Rectangle* rect_tab = new Rectangle[16];
	Rectangle* fire_balls = nullptr;
	Rectangle wall({ 10, 720 }, { 400, 0 });
	Rectangle used_rect({ 50, 50 }, { 170, 625 });

	int size_fire = 0;
	used_rect.setColor(sf::Color::Green);
	fill(rect_tab, 16);

	sf::Font intro_font;
	intro_font.loadFromFile("C:\\Users\\dan-c\\Desktop\\C++\\open-sans-font\\OpenSansBoldItalic-YWD4.ttf");
	
	Text_class *intro_text = new Text_class(intro_font, 24, "TYPE IN YOUR NICKNAME", 60, 45);
	intro_text->setStyle(sf::Text::Bold);

	string disc;
	disc = "Game is called 'Kill the most'\nKill your enemies with your Gun\n\nTuturial:\nuse('A') to go left\nuse('B') to go right\nuse('W') to fire a gun\nPress 'Enter' to start";
	Text_class *discription = new Text_class(intro_font, 18, disc, 60, 200);

	Text_class *ground = new Text_class(intro_font, 20, "//////////////////////////////////////////////////\n", 0, 670);
	ground->setFillColor(sf::Color::Cyan);

	Text_class *attic = new Text_class(intro_font, 20, "//////////////////////////////////////////////////\n", 0, 400);
	attic->setFillColor(sf::Color::Cyan);

	std::string score_Str = "YOU KILLED " + std::to_string(SCORE) + "\nYOU FAILED " + std::to_string(LOST);
	Text_class *score = new Text_class(intro_font, 20, score_Str, 60, 120);

	std::string input = "Nickname: ";
	Text_class *user_input = new Text_class(intro_font, 20, input, 60, 80);

	Text_class *press_enter = new Text_class(intro_font, 14, "PUT IN YOUR NICKNAME AND PRESS 'ENTER'\nYOU NEED TO SCORE 40 POINTS TO PASS", 60, 520);
	
	int x = rand() % 50;
	for (int i = 0; i < 5; i++) {
		rect_enemies[i].setColor(sf::Color::Red);
		rect_enemies[i].setEnemy();
		rect_enemies[i].setSize({ 30,30 });
		rect_enemies[i].setPosition(x, 370);
		x += 50 + rand() % 40;
	}

	///////////////////////////////////// START INTRO LOOP
	///////////////////////////////// INTRO 

	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			} break;
			case sf::Event::TextEntered: {
				if (START == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					char znak = event.key.code;
					if (event.key.code == 8 && input.length() > 10)
						change_str(input);
					if (input.length() <= 20 && event.key.code != 8)
						input += znak;
				}

			}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (input.length() >= 18) {
					START = 1;
					STOPPED_SHOWING = true;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				used_rect.moveA();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				used_rect.moveD();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (START == 1) {
					size_fire += 1;
					used_rect.fire(&fire_balls, size_fire);
				}
			}
		}
		score->setString("YOU KILLED " + std::to_string(SCORE) + "\nYOU FAILED " + std::to_string(LOST) + "      MAX 20");
		user_input->setString(input);
		window.clear();

		///////////////////////////////// INTRO 

		intro_text->draw_to(window);
		user_input->draw_to(window);
		discription->draw_to(window);
		attic->draw_to(window);
		ground->draw_to(window);
		score->draw_to(window);

		wall.draw_to(window);

		print_obj(window, rect_tab, 16);
		if (START == 1 && LOST < 21) {
			check_killed(fire_balls, size_fire, rect_enemies, 5, &SCORE, &LOST, 0);
			if (check_rect_enemy(used_rect, rect_enemies, 5))
				LOST = 21;
			print_enemies(window, rect_enemies, 5, 0);
			print_fire(window, fire_balls, size_fire, 0);
			used_rect.draw_to(window);

			if (SCORE >= 40) {
				break;
			}

		}
		if (LOST > 20) {
			window.clear();

			Text_class *lost = new Text_class(intro_font, 60, "YOU HAVEN'T PASSED THE TUTORIAL!\nPress 'ESCAPE' to quit", 150, 300);
			lost->draw_to(window);

		}
		if (!STOPPED_SHOWING) {
			press_enter->draw_to(window);
		}

		///////////////////////////////// INTRO 

		window.display();
	}
	
	clear_memory(&fire_balls);
	clear_memory(&rect_enemies);
	clear_memory(&rect_tab);

	///////////////////////////////////// END INTRO LOOP

	///////////////////////////////////// START MAIN GAME

	fire_balls = rect_enemies = rect_tab = nullptr;
	START = SCORE = LOST = size_fire = 0;

	// bonus' functions will be represented via using enemy's functions
	Rectangle* bonus = new Rectangle({20,20},{0,0});
	Text_class *score_up = new Text_class(intro_font, 20, "-----------------------------", 30, 45);
	Text_class *score_down = new Text_class(intro_font, 20, "-----------------------------", 30, 70);
	Text_class *score_text = new Text_class(intro_font, 20, "HIGHSCORE TABLE", 30, 60);
	Text_class *starting = new Text_class(intro_font, 30, "PRESS 'W' TO START PLAYING", 640, 45);
	Text_class *score_now = new Text_class(intro_font, 20, "YOUR SCORE: ", 30, 10);
	Text_class *input_w = new Text_class(intro_font, 20, "W", 180, 500);
	Text_class *input_a = new Text_class(intro_font, 20, "A", 130, 550);
	Text_class *input_d = new Text_class(intro_font, 20, "D", 230, 550);
	Text_class *board = new Text_class(intro_font, 20, "KEYBOARD", 145, 450);
	int checking_0 = 0;
	int checking = 0;
	int size_highscore = 0;
	int* TAB_highscore_int = nullptr;
	std::string *TAB_highscore = nullptr;

	ground->setString("///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
	ground->setPosition( 400, 680 );
	used_rect.setPosition( 800, 633 );
	starting->setFillColor(sf::Color::Yellow);
	bonus->setPosition(rand() % 820 + 410, 0);
	bonus->setColor(sf::Color::Cyan);
	bonus->setEnemy();

	rect_enemies = new Rectangle[10];
	x = rand() % 50 + 410;
	for (int i = 0; i < 10; i++) {
		rect_enemies[i].setColor(sf::Color::Red);
		rect_enemies[i].setEnemy();
		rect_enemies[i].setSize({ 30,30 });
		rect_enemies[i].setPosition(x, 20);
		x += 50 + rand() % 70;
	}

	Text_class *output_tab = new Text_class(intro_font, 20, "", 30, 130);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
			} break;
			case sf::Event::TextEntered: {

			}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				used_rect.moveA_main();
				input_a->setFillColor(sf::Color::Yellow);
				input_d->setFillColor(sf::Color::White);
				input_w->setFillColor(sf::Color::White);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				used_rect.moveD_main();
				input_a->setFillColor(sf::Color::White);
				input_d->setFillColor(sf::Color::Yellow);
				input_w->setFillColor(sf::Color::White);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (START == 1) {
					size_fire += 1;
					used_rect.fire(&fire_balls, size_fire);
				}
				else
					START = 1;
				input_w->setFillColor(sf::Color::Yellow);
				input_d->setFillColor(sf::Color::White);
				input_a->setFillColor(sf::Color::White);
			}
			else {	
				input_a->setFillColor(sf::Color::White);
				input_d->setFillColor(sf::Color::White);
				input_w->setFillColor(sf::Color::White);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		window.clear();
		score_now->setString("YOUR SCORE: " + std::to_string(SCORE) + " LOST: " + std::to_string(LOST));
		score_up->draw_to(window);
		score_text->draw_to(window);
		score_down->draw_to(window);
		ground->draw_to(window);
		score_now->draw_to(window);
		input_w->draw_to(window);
		input_a->draw_to(window);
		input_d->draw_to(window);
		board->draw_to(window);

		if (checking_0 == 0) {
			ifstream file_0("C:\\Users\\dan-c\\Desktop\\data.txt");
			if (!file_0) {
				cout << "ERROR WITH OPENING THE FILE\n";
				return 1;
			}

			int var;
			string str;

			while (file_0 >> str >> var) {
				size_highscore += 1;
				fill_highscore(&TAB_highscore, &TAB_highscore_int, size_highscore, str, var);
			}
			sort_highscore(&TAB_highscore, &TAB_highscore_int, size_highscore);
			checking_0 = 1;
		}

		if (START == 0) {
			starting->draw_to(window);
		}
		else if(START == 1 && LOST < 40) {
			check_bonus(fire_balls, size_fire, bonus, 1, &SCORE);
			check_killed(fire_balls, size_fire, rect_enemies, 10, &SCORE, &LOST, 1);
			if (check_rect_enemy(used_rect, rect_enemies, 10))
				LOST = 40;
			print_enemies(window, rect_enemies, 10, 1);
			print_fire(window, fire_balls, size_fire, 1);
			print_enemies(window, bonus, 1, 1);
		}
		else if (LOST == 40) {
			Text_class *end_main = new Text_class(intro_font, 30, "THANKS FOR THE GAME\nPRESS 'ESCAPE' TO QUIT", 700, 350);
			end_main->draw_to(window);
			
			if (checking == 0) {
				ofstream file("C:\\Users\\dan-c\\Desktop\\data.txt", ios::app);
				if (!file) {
					cout << "ERROR WITH OPENING FILE\n";
					return 1;
				}
				file << input.substr(10, input.length()) << " " << SCORE << "\n";
				checking = 1;
			}
		}

		string end_highscore = "";

		for (int i = 0; i < size_highscore && i < 10; i++) {
			end_highscore = end_highscore + to_string(i) + ". User: " + TAB_highscore[i] + " " + ", scored: " + to_string(TAB_highscore_int[i]) + "\n";
		}
		
		output_tab->setString(end_highscore);
		output_tab->draw_to(window);
		used_rect.draw_to(window);
		wall.draw_to(window);

		window.display();
	}

	clear_memory(&score_now);
	clear_memory(&score_down);
	clear_memory(&score_up);
	clear_memory(&score_text);
	clear_memory(&ground);
	clear_memory(&starting);
	clear_memory(&output_tab);
	clear_memory(&input_a);
	clear_memory(&input_d);
	clear_memory(&input_w);
	clear_memory(&TAB_highscore);
	clear_memory(&TAB_highscore_int);
	clear_memory(&fire_balls);
	clear_memory(&rect_enemies);

	///////////////////////////////////// END MAIN GAME
}