#pragma once
#include <SFML/Graphics.hpp>
#ifndef _STAGE
#define _STAGE

class Stage {
private:
	sf::RenderWindow &window;
	sf::RectangleShape top;
	sf::RectangleShape bottom;

public:
	float borderSize;

	Stage(sf::RenderWindow &window_, float borderSize_);

	void draw();
};

#endif