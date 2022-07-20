#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Map.hpp"

using namespace sf;

struct Enemy {
	float coordX = 0, coordY = 0;
	FloatRect rect;
	Sprite sprite;
	Texture textureDeath;
	float currentFrame;
	int direction = 1;
	bool isAlive;

	virtual void Set(Texture& image, int x, int y);

	Enemy() = default;

	virtual void Collision();


	virtual void Update(Texture& image);

};



void Enemy::Set(Texture& image, int x, int y) {
	sprite.setTexture(image);
	rect = FloatRect(x, y, 20, 20);

	coordX = 0.05;
	currentFrame = 0;
	isAlive = true;
}

void Enemy::Update(Texture& image) {
	rect.left += coordX;
	Collision();

	if (!isAlive) {
		sprite.setTexture(image);
	}
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

void Enemy::Collision() {
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			if (MAP[i][j] == 'W' || MAP[i][j] == 'I' || MAP[i][j] == 'L') {
				if (coordX > 0)
				{
					rect.left = j * 32 - rect.width; coordX *= -1;
				}
				else if (coordX < 0)
				{
					rect.left = j * 32 + 32;  coordX *= -1;
				}
			}
		}
	}
}