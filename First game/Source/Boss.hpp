#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Map.hpp"
#include "Enemy.hpp"

using namespace sf;

struct Boss :public Enemy {
	//float coordX = 0, coordY = 0;
	FloatRect rect;
	float currentFrame;
	int health = 10;
	int direction = 1;

	Boss() = default;

	virtual void Set(Texture& image, int x, int y) override;

	virtual void Update(Texture& image) override;

	virtual void Collision() override;
};

void Boss::Set(Texture& image, int x, int y) {
	sprite.setTexture(image);

	rect = FloatRect(x, y, 32, 32);
	coordY = 0.2;
	currentFrame = 0;
	isAlive = true;
}

void Boss::Update(Texture& image) {
	rect.top += coordY;

	Collision();

	if (health == 0) {
		isAlive = false;
		coordY = 0;
		sprite.setTexture(image);
	}

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

void Boss::Collision() {
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			if (MAP[i][j] == 'W') {
				if (coordY > 0)
				{
					rect.top = i * 32 - rect.height; 
					coordY *= -1;
				}
				else if (coordY < 0)
				{
					rect.top = i * 32 + 32;  
					coordY *= -1;
				}
			}
		}
	}
}