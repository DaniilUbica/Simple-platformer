#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

Texture textureTitle;
Texture texturePlay;
Texture textureExit;
Texture textureHurt;
Texture textureIdle;
Texture textureRun;
Texture textureJump;
Texture textureFall;
Texture textureBackground;
Texture textureHeal;
Texture textureHeart;
Texture textureDeath;
Texture textureBullet;
Texture textureAttack;
Texture textureLevel;
Texture textureHurtFloor;
Texture textureHurtFloorTop;
Texture textureEnemy;
Texture textureTopEnemy;
Texture textureTopEnemyDead;
Texture textureDeadEnemy;
Texture textureTile;
Texture textureSupportTile;
Texture textureTopSupportTile;
void setTextures() {
	textureTitle.loadFromFile("Assets/Title.png");
	texturePlay.loadFromFile("Assets/Play.png");
	textureExit.loadFromFile("Assets/Exit.png");
	textureHurt.loadFromFile("Assets/Punk_hurt.png");
	textureIdle.loadFromFile("Assets/Punk_idle.png");
	textureRun.loadFromFile("Assets/Punk_run.png");
	textureJump.loadFromFile("Assets/Punk_jump.png");
	textureFall.loadFromFile("Assets/Punk_fall.png");
	textureBackground.loadFromFile("Assets/Background.png");
	textureHeal.loadFromFile("Assets/Box1.png");
	textureHeart.loadFromFile("Assets/Heart.png");
	textureDeath.loadFromFile("Assets/Punk_death.png");
	textureBullet.loadFromFile("Assets/Bullet.png");
	textureAttack.loadFromFile("Assets/Punk_attack3.png");
	textureLevel.loadFromFile("Assets/NextLevel.png");
	textureHurtFloor.loadFromFile("Assets/Horn.png");
	textureHurtFloorTop.loadFromFile("Assets/RotatedHorn.png");
	textureEnemy.loadFromFile("Assets/Barrel2.png");
	textureTopEnemy.loadFromFile("Assets/Barrel2_2.png");
	textureTopEnemyDead.loadFromFile("Assets/Barrel3_2.png");
	textureDeadEnemy.loadFromFile("Assets/Barrel3.png");
	textureTile.loadFromFile("Assets/IndustrialTile_25.png");
	textureSupportTile.loadFromFile("Assets/IndustrialTile_62.png");
	textureTopSupportTile.loadFromFile("Assets/TopIndustrialTile_62.png");
}