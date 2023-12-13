#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include "Player.h"
#include "P_enemy.h"
#include "Map.h"

#define kube 102

void EndWindow(Texture& end_game_png, Text text_end, Text text_exit);
Text Create_Text(Font& font, int size, Color color, float x, float y, String title);
void PrintMap(Texture& beer_png, Texture& sprite_png, Texture& lobster_png, Texture& ganteli_png, int offsetX, int left_beer);

using namespace sf;
RenderWindow window(VideoMode(w_win, h_win), "BeerMan", Style::Fullscreen);// Style::Fullscreen

void EndWindow(Texture& end_game_png, Text text_end, Text text_exit) {
	Event event;
	Sprite end_game;
	end_game.setTexture(end_game_png);
	end_game.setScale(w_win / end_game.getLocalBounds().width / 2, h_win / end_game.getLocalBounds().height / 2);
	end_game.setPosition(w_win / 3, h_win / 3.5);

	window.clear(Color::White);
	window.draw(end_game);
	window.draw(text_end);
	window.draw(text_exit);
	window.display();

	while (!Keyboard::isKeyPressed(Keyboard::Escape) && !Joystick::isButtonPressed(0, 3)) {
		window.pollEvent(event); Sleep(10);}
	window.close();
}

Text Create_Text(Font &font, int size, Color color, float x, float y, String title) {
	Text text;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setStyle(Text::Bold);
	text.setPosition(x, y);
	text.setString(title);
	return text;
}

int Total_Item(char x) {
	int total = 0;
	for (int i = 0; i < h_map; i++)
		for (int j = 0; j < w_map; j++)
			if (TitleMap[i][j] == x) total++;
	return total;
}

void PrintMap(Texture& beer_png, Texture& sprite_png, Texture& lobster_png, Texture& ganteli_png, int offsetX, int left_beer) {
	int max_X, min_X;

	max_X = (offsetX + w_win * 1.25)/kf;
	if (max_X > w_map) max_X = w_map;
	min_X = (offsetX)/kf;
	if (min_X < 0) min_X = 0;

	RectangleShape rectangle(Vector2f(kf, kf));
	Sprite beer, sprite, lobster, ganteli;
		sprite.setTexture(sprite_png);
		beer.setTexture(beer_png);
		beer.setScale(kf / beer.getLocalBounds().width, kf / beer.getLocalBounds().height);
		ganteli.setTexture(ganteli_png);
		ganteli.setScale(kf / ganteli.getLocalBounds().width, kf / ganteli.getLocalBounds().height);
		lobster.setTexture(lobster_png);
		lobster.setScale(kf / lobster.getLocalBounds().width, kf / lobster.getLocalBounds().height);
	for (int i = 0; i < h_map; i++)
		for (int j = min_X; j < max_X; j++) {
			if (TitleMap[i][j] == '8' && !left_beer) TitleMap[i][j] = '9';

			switch (TitleMap[i][j])
			{
			case '1': //пиво
				beer.setPosition(j * kf - offsetX, i * kf);
				window.draw(beer); continue;
			case '8'://дверь 2*Y закрытая
				sprite.setTextureRect(IntRect(kube * 8 + 4, kube * 5 + 1, kube, 2 * kube));
				sprite.setScale(kf / sprite.getLocalBounds().width, 2 * kf / sprite.getLocalBounds().height);
				sprite.setPosition(j * kf - offsetX, i * kf);
				window.draw(sprite); continue;
			case '9'://дверь 2*Y открытая
				sprite.setTextureRect(IntRect(kube * 5 + 4, kube * 5 + 3, kube, 2 * kube));
				sprite.setScale(kf / sprite.getLocalBounds().width, 2 * kf / sprite.getLocalBounds().height);
				sprite.setPosition(j * kf - offsetX, i * kf);
				window.draw(sprite); continue;
			case 'L': //лобстер
				lobster.setPosition(j * kf - offsetX, i * kf);
				window.draw(lobster); continue;
			case '+': //гантели
				ganteli.setPosition(j * kf - offsetX, i * kf);
				window.draw(ganteli); continue;
			case 'C': //небо
				rectangle.setFillColor(Color::Blue);
				rectangle.setPosition(j * kf - offsetX, i * kf);
				window.draw(rectangle); continue;
			case 'S'://вода 2*Y
				sprite.setTextureRect(IntRect(kube * 4 + 3, 1, kube, 2 * kube));
				sprite.setScale(kf / sprite.getLocalBounds().width, 2 * kf / sprite.getLocalBounds().height);
				sprite.setPosition(j * kf - offsetX, i * kf);
				window.draw(sprite); continue;
			default:
				break;
			}

			switch (TitleMap[i][j]) { //sprite cube
			case 'O'://земля
				sprite.setTextureRect(IntRect(kube * 3 + 3,	1,			  kube, kube)); break;
			case 'G'://земля c стравой
				sprite.setTextureRect(IntRect(3,			1,			  kube, kube)); break;
			case 'B'://деревянынй куб
				sprite.setTextureRect(IntRect(kube * 3 + 3, kube * 3 + 1, kube, kube)); break;
			case 'I'://конец забора
				sprite.setTextureRect(IntRect(2,			kube * 4 + 1, kube, kube)); break;
			case 'W'://забор
				sprite.setTextureRect(IntRect(kube + 1,		kube * 4 + 2, kube, kube)); break;
			case 'F'://фанера
				sprite.setTextureRect(IntRect(kube * 4 + 2, kube * 5 + 2, kube, kube)); break;
			case 'K'://камень
				sprite.setTextureRect(IntRect(kube * 3 + 3, kube + 1,	  kube, kube)); break;
			case 'Z'://камень с травой
				sprite.setTextureRect(IntRect(3,			kube + 1,	  kube, kube)); break;
			case 'V'://иглы
				sprite.setTextureRect(IntRect(4,			kube * 6 + 3, kube, -kube)); break;
			case 'T'://трава
				sprite.setTextureRect(IntRect(kube * 2 + 2, kube * 6 + 2, kube, -kube)); break;
			default:
				continue;
			}
			sprite.setScale(kf / sprite.getLocalBounds().width, kf / sprite.getLocalBounds().height);
			sprite.setPosition(j * kf - offsetX, i * kf);
			window.draw(sprite);
			
		}
}


int main()
{
	srand(time(NULL)); (float)rand() / RAND_MAX;
	float time, joystick_x;
	int offsetX = 0, total_enemy = 0;
	char title_score[100];

	window.setFramerateLimit(30);
	window.setMouseCursorVisible(false);

	Sprite intro;
	Texture person_png, beer_png, end_game_png, sprite_png, lobster_png, ganteli_png, intro_png, sport_png;
	if (!person_png.loadFromFile("_png/walk2.png")) return 0;
	if (!beer_png.loadFromFile("_png/beer.png")) return 0;
	if (!end_game_png.loadFromFile("_png/end.png")) return 0;
	if (!sprite_png.loadFromFile("_png/sprite2.png")) return 0;
	if (!lobster_png.loadFromFile("_png/lobster.png")) return 0;
	if (!ganteli_png.loadFromFile("_png/gant.png")) return 0;
	if (!intro_png.loadFromFile("_png/intro.png")) return 0;
	if (!sport_png.loadFromFile("_png/sport.png")) return 0;
	PLAYER p(person_png);
	p.left_beer = Total_Item('1');

	ENEMY *dog = new ENEMY[Total_Item('M')];
	for (int i = 0; i < h_map; i++)
		for (int j = 0; j < w_map; j++)
			if (TitleMap[i][j] == 'M') {
				dog[total_enemy+0].create(sport_png, j, i); 
				TitleMap[i][j] = ' ';
				total_enemy++;

			}

	Font font; Text text_score, text_end, text_exit, text_exit0;
	if (!font.loadFromFile("_font/font.ttf")) return 0;
	sprintf_s(title_score, "Need a beer - %d", p.left_beer);
	text_score = Create_Text(font, 50, Color::Yellow, w_win * 0.85, 0,			  title_score);
	text_end   = Create_Text(font, 50, Color::Black,  w_win * 0.20, h_win * 0.10, L"Ты самый чёткий пацанчик на районе!!!");
	text_exit  = Create_Text(font, 50, Color::Black,  w_win * 0.30, h_win * 0.90, L"Но лучше спортом займись :)\n	Для выхода нажми Esc");
	text_exit0 = Create_Text(font, 40, Color::Black,  kf + kf/4,	kf/6,		  L"Выход из игры - Esc");

	Sound jump_sd, beer_sd, lobster_sd, return_sd, water_sd; Music music;
	SoundBuffer buffer_jp, buffer_br, buffer_lb, buffer_rt, buffer_wt;
	if (!buffer_jp.loadFromFile("_music/jump.wav")) return 0;
	if (!buffer_br.loadFromFile("_music/pivo.wav")) return 0;
	if (!buffer_lb.loadFromFile("_music/lobster.wav")) return 0;
	if (!buffer_rt.loadFromFile("_music/return.wav")) return 0;
	if (!buffer_wt.loadFromFile("_music/water.wav")) return 0;
	if (!music.openFromFile("_music/walk.wav")) return 0;
	lobster_sd.setBuffer(buffer_lb);
	return_sd.setBuffer(buffer_rt);
	jump_sd.setBuffer(buffer_jp);
	beer_sd.setBuffer(buffer_br);
	water_sd.setBuffer(buffer_wt);
	music.setLoop(true);
	music.play();

	intro.setTexture(intro_png);
	intro.setScale(w_win*1.2 / intro.getLocalBounds().width, h_win*1.15 / intro.getLocalBounds().height);
	intro.setPosition(0, 0);
	window.draw(intro);
	window.display();
	Event event;
	while (!Keyboard::isKeyPressed(Keyboard::Enter) && !Joystick::isButtonPressed(0, 0)) {
		window.pollEvent(event); Sleep(10);}
	Sleep(500);
	Clock clock; 
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		window.clear(Color::White);
		window.pollEvent(event);

		if (Joystick::isConnected(0)) {
			joystick_x = Joystick::getAxisPosition(0, Joystick::X) /100;
			if (abs(joystick_x) > 0.15) p.dx = p.speed_val * joystick_x;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) p.dx = -p.speed_val;
		if (Keyboard::isKeyPressed(Keyboard::Right)) p.dx = p.speed_val;
		if (Keyboard::isKeyPressed(Keyboard::Escape) || Joystick::isButtonPressed(0, 7)) window.close();
		if (Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0, 0))
			if (p.onGround) { p.dy = p.jump_val; jump_sd.play(); }

		p.update(time, offsetX);
		for (int i = 0; i < total_enemy; i++) {
			dog[i].update(time, offsetX);
			if (dog[i].rect.intersects(p.rect)) p.return_start = true;
			window.draw(dog[i].sprite);
		}

		if (p.rect.left > w_win / 2)	offsetX = p.rect.left - w_win / 2;
		else offsetX = 0;
		window.draw(p.sprite);
		PrintMap(beer_png, sprite_png, lobster_png, ganteli_png, offsetX, p.left_beer);

		if (p.sound_lobster) { p.sound_lobster = false; lobster_sd.play(); }
		if (p.sound_water) { p.sound_water = false; water_sd.play(); }
		if (p.return_start) {
			p.rect.top = p.start_y; p.rect.left = p.start_x;
			p.dx = p.dy = 0; p.return_start = false;
			return_sd.play(); }
		if (p.sound_beer) {
			sprintf_s(title_score, "Need a beer - %d", p.left_beer);
			text_score.setString(title_score);
			p.sound_beer = false;
			beer_sd.play();
		}

		window.draw(text_score);
		window.draw(text_exit0);
		window.display();
		
		if (p.isEndGame) EndWindow(end_game_png, text_end, text_exit);
	}
	delete[] dog;
	return 0;
}