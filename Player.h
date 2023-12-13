#pragma once
#include "Map.h"

#define w_man 54
#define h_man 104

using namespace sf;
class PLAYER {
public:
	Sprite sprite;
	FloatRect rect;
	int left_beer, start_x, start_y;
	float dx, dy, speed_val, jump_val, currentFrame;
	bool onGround, sound_beer, sound_lobster, sound_water, return_start, isEndGame;

	PLAYER(Texture& image) {
		start_x = 70;
		start_y = h_win - kf - 10;
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(0, 0, w_man, h_man));
		rect = FloatRect(70, h_win - kf-10, w_man, h_man);

		dx = dy = 0;
		left_beer = 0;
		speed_val = 0.1; 
		jump_val = -0.4;
		currentFrame = 0;
		onGround = sound_beer = sound_lobster = sound_water = return_start = isEndGame = false;
	}

	void update(float time, int offsetX) {
		if(!onGround) dy += time / 3000;
		onGround = false;

		rect.left += dx * time;
		Collision("dx");
		rect.top += dy * time;
		Collision("dy");

		if (dx) {
			currentFrame += time / 200;
			if (currentFrame > 5) currentFrame -= 5;
			if (dx > 0) sprite.setTextureRect(IntRect(w_man * int(currentFrame), 0, w_man, h_man));
			if (dx < 0) sprite.setTextureRect(IntRect(w_man * int(currentFrame) + w_man, 0, -w_man, h_man));
		}
		else
			sprite.setTextureRect(IntRect(w_man * 4, 0, w_man, h_man));

		sprite.setPosition(rect.left - offsetX, rect.top);
		dx = 0;
	}

	void Collision(String way) {
		for (int i = rect.top / kf; i < (rect.top + rect.height) / kf; i++)
			for (int j = rect.left / kf; j < (rect.left + rect.width) / kf; j++) {
				if (TitleMap[i][j] == '1') {
					TitleMap[i][j] = ' ';
					speed_val += 0.01;
					jump_val  -= 0.01;
					sound_beer = true;
					left_beer--;}
				if (TitleMap[i][j] != ' ') {
					if ((dx > 0) && (way == "dx")) rect.left = j * kf - rect.width;
					if ((dx < 0) && (way == "dx")) rect.left = j * kf + kf;

					if ((dy > 0) && (way == "dy")) { rect.top = i * kf - rect.height; dy = 0; onGround = true; }
					if ((dy < 0) && (way == "dy")) { rect.top = i * kf + kf; dy = 0;}}

				if (TitleMap[i][j] == '9') isEndGame = true;
				if (TitleMap[i][j] == 'S') sound_water = true;
				if (TitleMap[i][j] == 'L') {
					sound_lobster = true; 
					dy = jump_val * 1.25; }
				if (TitleMap[i][j] == 'S' || TitleMap[i][j] == 'V' || TitleMap[i][j] == '+') {
					return_start = true;
					return;
				}

			}
	}
};
