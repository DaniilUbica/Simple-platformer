#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include "Map.hpp"
#include "Animation.hpp"

using namespace sf;

struct Player {
	bool onTheFloor = false;
	float coordX, coordY;
	bool onGround;
	int health = 5;
	float currentFrame;
	int direction = -1;
	bool onTop = false;
	bool isFalling = false;
	bool onTopGround = false;
	float timer;

	FloatRect rect;
	Sprite sprite;
	AnimationManager animation;

	void Collision(int dir);

	Player() = default;

	Player(AnimationManager &a);

	void Update(bool &isHurted, float &time);

};

Player::Player(AnimationManager& a) {
	rect = FloatRect(240, 327, 29, 33);
	coordX = 0;
	coordY = 0;
	currentFrame = 0;
	animation = a;
}

void Player::Update(bool& isHurted, float &time) {
	if (health > 0) {
		rect.left += coordX * time;
		Collision(0);
		isFalling = false;
		onGround = false;
		onTopGround = false;
		//canShoot = true;

		if (!onGround && onTop == false) {
			coordY = coordY + 0.0008 * time;
			isFalling = true;
		}
		if (!onTopGround && onTop == true) {
			coordY = coordY - 0.0008 * time;
			isFalling = true;
		}
		rect.top += coordY * time;

		if (coordX < 0) {
			direction = -1;
		}

		if (coordX > 0) {
			direction = 1;
		}

		timer = 0;
		Collision(1);

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		coordX = 0;
	}
	else {
		if (!onGround && onTop == false) {
			coordY = coordY + 0.0008 * time;
			isFalling = true;
		}
		if (!onTopGround && onTop == true) {
			coordY = coordY - 0.0008 * time;
			isFalling = true;
		}
		rect.top += coordY;
		Collision(1);
	}
}

void Player::Collision(int dir) {
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			if (MAP[i][j] == 'W') {
				if (coordY > 0 && dir == 1) {
					rect.top = i * 32 - rect.height;
					onGround = true;
					isFalling = false;
					coordY = 0;
				}
				if (coordY < 0 && dir == 1) {
					rect.top = i * 32 + 32;
					onTopGround = true;
					isFalling = false;
					coordY = 0;
				}
				if (coordX > 0 && dir ==0) {
					rect.left = j * 32 - rect.width;
				}
				if (coordX < 0 && dir == 0) {
					rect.left = j * 32 + 32;
				}
			}
			if (MAP[i][j] == '0') {
				MAP[i][j] = ' ';
				onTop = true;
				onTopGround = false;
			}
			if (MAP[i][j] == '9') {
				MAP[i][j] = ' ';
				onTop = false;
				onTopGround = false;
			}
			if (MAP[i][j] == 'H') {
				MAP[i][j] = ' ';
				if (health < 5) {
					health += 1;
				}
			}
			if (MAP[i][j] == 'D') {
				health -= 5;
			}
			if (MAP[i][j] == 'S') {
				coordY = 0.4;
				health -= 1;
			}
			if (MAP[i][j] == 'I') {
				continue;
			}
			if (MAP[i][j] == 'L') {
				rect.left += 64;
				MAP[i][j] = 'W';
			}
		}
	}
}