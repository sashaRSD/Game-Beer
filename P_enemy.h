#pragma once
#include "Map.h"


using namespace sf;
class ENEMY {
public:
	Sprite sprite;
	FloatRect rect;
	int left_beer, horizon;
	float dx, h_sport_orig, w_sport_orig;


	void create(Texture& image, int x, int y) {
		dx = random_float(0.06, 0.10);
		sprite.setTexture(image);
		h_sport_orig = sprite.getLocalBounds().height;
		w_sport_orig = sprite.getLocalBounds().width;
		sprite.setScale(2 * kf / sprite.getLocalBounds().width, 2 * kf / sprite.getLocalBounds().height);

		sprite.setTextureRect(IntRect(0, 0, w_sport_orig, h_sport_orig));
		rect = FloatRect(x * kf, (y-1) * kf, 2*kf, 2*kf);
	}


	void update(float time, int offsetX) {
		rect.left += dx * time;
		horizon = rect.top / kf +1;

		for (int j = rect.left / kf; j < (rect.left + rect.width) / kf; j++) {
			if (TitleMap[horizon][j] != ' ') 
				if  (dx > 0) { rect.left = j * kf - rect.width; dx *= -1; }
				else if (dx < 0) { rect.left = j * kf + kf; dx *= -1; }
		}

		if (dx > 0) sprite.setTextureRect(IntRect(0,			0, w_sport_orig,  h_sport_orig));
		if (dx < 0) sprite.setTextureRect(IntRect(w_sport_orig, 0, -w_sport_orig, h_sport_orig));

		sprite.setPosition(rect.left - offsetX, rect.top);
	}

	float random_float(float min, float max) {
		return ((float)rand() / RAND_MAX) * (max - min) + min;
	}
};
