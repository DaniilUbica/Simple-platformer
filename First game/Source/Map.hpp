#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int MAP_HEIGHT = 12;
const int MAP_WIDTH = 80;

float offsetX = 0, offsetY = 0;

String MAP[MAP_HEIGHT] = {

		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
		"W          L     I    9   W   9           WWWWWW     WWWWWWWWWWWWDDDDDDWDDDDDDDW",
		"W  H       W              W               W   9          9  W        W W       W",
		"W WW       W HI  I        WH       W W      0              W          0        W",
		"W0         WWWW   WWWWWWWWWWWWWWW       W   W              W    W     W        W",
		"WW     W   W       W                  0  WWWW              W W     W   W       W",
		"W          WW      W     I    I     WWWW                  WW   W         W     W",
		"W   I     WW  I    W     WWWWWW  W                        L        W           W",
		"W    WWWWWW   WWWWWWW   W W                               W   WW               W",
		"WW        W  I   L     WW                              WWWWWWWW                W",
		"W         W      W      WDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDWDDDDDDDDDDDDDDDDDDDDDW",
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
};
