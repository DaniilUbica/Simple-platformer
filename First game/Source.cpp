#include <SFML/Graphics.hpp>
#include <time.h>
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"
#include "Textures.h"
#include <iostream>

using namespace sf;

const int WINDOW_HEIGHT = 384;
const int WINDOW_WIDTH = 1280;
const int EnemiesMount = 6;
const int TopEnemiesMount = 12;
bool isHurted = false;
int counter = 0;
bool play = false, menu = true;

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jumping Punk!");

	setTextures();

	Sprite title(textureTitle);
	title.setScale(0.5, 0.5);
	title.setPosition(270, -100);
	Sprite playGame(texturePlay);
	playGame.setScale(0.5, 0.5);
	playGame.setPosition(160, 10);
	Sprite exit(textureExit);
	exit.setScale(0.5, 0.5);
	exit.setPosition(380, 10);

	Sprite tile;
	Sprite life[5];

	Sprite background(textureBackground);

	AnimationManager animation;

	Player player(animation);

	animation.CreateAnimation("Idle", textureIdle, 0, 15, 29, 33, 4, 0.005, 48);
	animation.CreateAnimation("Run", textureRun, 0, 15, 29, 33, 6, 0.008, 48);
	animation.CreateAnimation("Jump", textureJump, 0, 15, 29, 33, 4, 0.005, 48);
	animation.CreateAnimation("Hurt", textureHurt, 0, 15, 29, 33, 3, 0.005, 48);
	animation.CreateAnimation("Fall", textureJump, 0, 15, 29, 33, 4, 0.005, 48);
	animation.CreateAnimation("Attack", textureAttack, 240, 15, 29, 33, 1, 0.005, 48);
	animation.CreateAnimation("Death", textureDeath, 0, 15, 29, 33, 6, 0.005, 48);

	Bullet bullet(textureBullet);

	Enemy Enemies[EnemiesMount];
	for (int i = 0; i < EnemiesMount; i++) {
		Enemies[0].Set(textureEnemy, 224, 230);
		Enemies[1].Set(textureEnemy, 704, 102);
		Enemies[2].Set(textureEnemy, 804, 102);
		Enemies[3].Set(textureEnemy, 420, 102);
		Enemies[4].Set(textureEnemy, 570, 230);
		Enemies[5].Set(textureEnemy, 864, 198);
	}
	Enemy TopEnemies[TopEnemiesMount];
	for (int i = 0; i < TopEnemiesMount; i++) {
		TopEnemies[0].Set(textureTopEnemy, 224, 32);
		TopEnemies[1].Set(textureTopEnemy, 928, 32);
		TopEnemies[2].Set(textureTopEnemy, 704, 32);
		TopEnemies[3].Set(textureTopEnemy, 605, 32);
		TopEnemies[4].Set(textureTopEnemy, 500, 288);
		TopEnemies[5].Set(textureTopEnemy, 937, 32);
		TopEnemies[6].Set(textureTopEnemy, 1000, 32);
		TopEnemies[7].Set(textureTopEnemy, 900, 32);
		TopEnemies[8].Set(textureTopEnemy, 745, 32);
		TopEnemies[9].Set(textureTopEnemy, 1050, 32);
		TopEnemies[10].Set(textureTopEnemy, 1600, 32);
	}

	Clock clock;
	Clock clock2;
	RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen()) {


		float time = clock.getElapsedTime().asSeconds();
		float time2 = clock2.getElapsedTime().asMicroseconds();
		clock.restart();
		clock2.restart();

		time2 /= 800;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					Vector2i pos = Mouse::getPosition(window);
					if (menu) {
						if (pos.x >= 630 && pos.x <= 730 && pos.y >= 170 && pos.y <= 220) {
							window.close();
						}
						if (pos.x >= 410 && pos.x <= 510 && pos.y >= 170 && pos.y <= 220) {
							menu = false;
							play = true;
						}
					}
				}
			}
		}
		if (play) {
			for (int i = 0; i < 5; i++) {
				life[i].setTexture(textureHeart);
				life[i].setPosition(5 + 25 * i, 5);
			}
		}
		if (player.health > 0) {
			if (player.direction == 1)
				animation.Set("Idle");
			else {
				animation.Set("Idle");
				animation.Flip(true);
			}
			if (play == true) {
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					player.coordX = -0.15;
					animation.Set("Run");
					animation.Flip(true);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					player.coordX = 0.15;
					animation.Set("Run");
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					animation.Set("Jump");
					if (player.onGround == true) {
						player.coordY = -0.33;
						player.onGround = false;
					}
				}

				if (Keyboard::isKeyPressed(Keyboard::Up) && player.onTop == true) {
					animation.Set("Jump");
					if (player.onTopGround == true) {
						player.coordY = 0.33;
						player.onTopGround = false;
					}
				}
			}
			if (player.isFalling) {
				if (player.direction == 1)
					animation.Set("Fall");
				else {
					animation.Set("Fall");
					animation.Flip(true);
				}
			}

			if (player.onTop) {
				if (player.direction == 1) {
					animation.Rotate(true);
				}
				else {
					animation.RotateFlip(true);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (player.coordX == 0) {
				if (player.direction == 1) {
					animation.Set("Attack");
				}
				else {
					animation.Set("Attack");
					animation.Flip(true);
				}
			}
			if (player.onTop) {
				if (player.coordX == 0) {
					if (player.direction == 1) {
						animation.Set("Attack");
						animation.Rotate(true);
					}
					else {
						animation.Set("Attack");
						animation.RotateFlip(true);
					}
				}
			}
		
			if (bullet.go == 0) {
				if (player.direction == 1 && player.coordX == 0) {
					bullet.sprite.setScale(1, 1);
					bullet.go = 1;
					bullet.rect.left = player.rect.left + 67;
					bullet.rect.top = player.rect.top + 3;
				}
				else if (player.direction == -1 && player.coordX == 0){
					bullet.sprite.setScale(-1, 1);
					bullet.go = 2;
					bullet.rect.left = player.rect.left -12;
					bullet.rect.left = player.rect.left + 15;
				}
			}
		}
			if (bullet.go == 0) {
				bullet.rect.left = player.rect.left;
				bullet.rect.top = player.rect.top;
			}
			else if (bullet.go == 1) {
				bullet.coordX = 0.5;
			}
			else if (bullet.go == 2) {
				bullet.coordX = -0.5;
			}

		if (player.health > 0) {
			for(int i = 0; i<EnemiesMount; i++) {
				if (player.rect.intersects(Enemies[i].rect) && Enemies[i].isAlive) {
					if (player.coordY > 0) {
						Enemies[i].coordX = 0;
						player.coordY = -0.2;
						Enemies[i].isAlive = false;
					}
					else {
						animation.Set("Hurt");
						isHurted = true;
						if (player.coordX > Enemies[i].coordX) {
							player.rect.left -= 100;
							player.health -= 1;
						}
						else {
							player.rect.left += 100;
							player.health -= 1;
							if (i == 0) {
								player.rect.left = 321;
								player.rect.top = 191;
							}
						}
					}
				}
				if (bullet.rect.intersects(Enemies[i].rect) && Enemies[i].isAlive && bullet.go != 0) {
					Enemies[i].coordX = 0;
					Enemies[i].isAlive = false;
				}
			}
			for (int i = 0; i < TopEnemiesMount; i++) {
				if (player.rect.intersects(TopEnemies[i].rect) && TopEnemies[i].isAlive) {
					if (player.coordY < 0) {
						TopEnemies[i].coordX = 0;
						player.coordY = 0.2;
						TopEnemies[i].isAlive = false;
					}
					else {
						animation.Set("Hurt");
						isHurted = true;
						if (player.coordX > Enemies[i].coordX) {
							player.rect.left -= 100;
							player.health -= 1;
							if (i == 0) {
								player.rect.left = 32;
								player.rect.top = 32;
							}
						}
						else {
							player.rect.left += 100;
							player.health -= 1;
							if (i == 0) {
								player.rect.left = 310;
								player.rect.top = 32;
							}
						}
					}
				}
				if (bullet.rect.intersects(TopEnemies[i].rect) && TopEnemies[i].isAlive && bullet.go!=0) {
					TopEnemies[i].coordX = 0;
					TopEnemies[i].isAlive = false;
				}
			}
			for (int i = 0; i < EnemiesMount; i++) {
				Enemies[i].Update(textureDeadEnemy);
			}
			for (int i = 0; i < TopEnemiesMount; i++) {
				TopEnemies[i].Update(textureTopEnemyDead);
			}
		}
		else {
			player.sprite.setColor(Color::White);
		}

		player.Update(isHurted, time2);
		animation.Tick(time2);
		bullet.Update(time);

		//std::cout << player.rect.left << "; " << player.rect.top << "\n";

		if(player.rect.left > WINDOW_WIDTH/2) offsetX = player.rect.left - WINDOW_WIDTH/2;

		window.clear(Color::White);

		animation.Draw(window,player.rect.left - offsetX,player.rect.top - offsetY);

		if (bullet.go != 0) {
			window.draw(bullet.sprite);
		}

		for (int i = 0; i < MAP_HEIGHT; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				if (MAP[i][j] == 'W') {
					tile.setTexture(textureTile);
				 }
				if (MAP[i][j] == '0') {
					tile.setTexture(textureSupportTile);
				}
				if (MAP[i][j] == '9') {
					tile.setTexture(textureTopSupportTile);
				}
				if (MAP[i][j] == ' ' || MAP[i][j] == 'I') {
					continue;
				}
				if (MAP[i][j] == 'H') {
					tile.setTexture(textureHeal);
				}
				if (MAP[i][j] == 'D') {
					tile.setTexture(textureHurtFloor);
				}
				if (MAP[i][j] == 'S') {
					tile.setTexture(textureHurtFloor);
				}
				if (MAP[i][j] == 'L') {
					tile.setTexture(textureLevel);
				}
				tile.setPosition(j * 32 - offsetX, i * 32 - offsetY); 
				window.draw(tile);
			}
		}

		for (int i = 0; i < EnemiesMount; i++) {
			window.draw(Enemies[i].sprite);
		}
		for (int i = 0; i < TopEnemiesMount; i++) {
			window.draw(TopEnemies[i].sprite);
		}
		for (int i = 0; i < player.health; i++) {
			window.draw(life[i]);
		}
		if (menu) {
			window.draw(title);
			window.draw(playGame);
			window.draw(exit);
		}
		window.draw(player.sprite);
		window.display();
	}
}
