#include <SFML/Graphics.hpp>
#include "stage.h"

Stage::Stage(sf::RenderWindow &window_, float borderSize_) : window{ window_ }, borderSize{ borderSize_ } {
	sf::Vector2u windowSize = window.getSize();
	top = sf::RectangleShape(sf::Vector2f(windowSize.x, (float)windowSize.y * borderSize));
	bottom = sf::RectangleShape(sf::Vector2f(windowSize.x, (float)windowSize.y * borderSize));
	bottom.setPosition(sf::Vector2f(0.f, windowSize.y - windowSize.y*borderSize));
	top.setFillColor(sf::Color(230, 230, 230, 255));
	bottom.setFillColor(sf::Color(230, 230, 230, 255));
};

void Stage::draw() {
	window.draw(top);
	window.draw(bottom);
}