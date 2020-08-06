#pragma once
#include <SFML/Graphics.hpp>
#include "stage.h"
#ifndef _PLAYER
#define _PLAYER
class Player {
private:
	float vsize;
	float hsize = 0.03f;
	float spacing;
	int id;
	Stage stage;
	sf::RenderWindow &window;



public:
	sf::RectangleShape rectangle;
	int score;
	Player(sf::RenderWindow &window_, float vsize_, float spacing_, int id_, Stage &stage_, int score_ = 0);

	bool checkCollision();

	void draw();
};

#endif