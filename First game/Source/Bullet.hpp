#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Map.hpp"
#include "Player.hpp"

using namespace sf;

struct Bullet {
	float coordX, coordY;
	FloatRect rect;
	int go;
	float timer;
	Sprite sprite;
	Player player;

	Bullet(Texture& image);

	void Update(float time);

	void Collision(int dir);
};

Bullet::Bullet(Texture& image) {
	rect = FloatRect(player.rect.left, 50, 9, 22);
	sprite.setTexture(image);
	coordX = coordY = 0;
	timer = 0;
	go = 0;
}

void Bullet::Update(float time) {
	rect.left += coordX;
	Collision(0);
	rect.top += coordY;
	Collision(1);
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	timer += time;
}

void Bullet::Collision(int dir) {
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			if (MAP[i][j] == 'W' || timer>0.5) {
				if ((coordX > 0 && dir == 0) || (coordX < 0 && dir == 0)) {
					timer = 0;
					go = 0;
				}
			}
		}
	}
}