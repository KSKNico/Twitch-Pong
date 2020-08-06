#include "player.h"

Player::Player(sf::RenderWindow &window_, float vsize_, float spacing_, int id_, Stage &stage_, Irctwitch &irc_, int score_) : window{window_}, 
	vsize{ vsize_ }, spacing{ spacing_ }, id{ id_ }, stage{stage_}, irc {irc_}
{
	sf::Vector2u windowSize = window.getSize();
	rectangle = sf::RectangleShape(sf::Vector2f(hsize * windowSize.x, vsize * windowSize.y));
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	if (id == 0) {
		rectangle.setPosition(windowSize.x * spacing, windowSize.y / 2);
		rectangle.setFillColor(sf::Color::Blue);
	}
	else if (id == 1) {
		rectangle.setPosition(windowSize.x - windowSize.x * spacing, windowSize.y / 2);
		rectangle.setFillColor(sf::Color::Red);
	}
};

bool Player::checkCollision() {
	sf::Vector2u windowSize = window.getSize();
	if (stage.borderSize * windowSize.y > rectangle.getPosition().y - rectangle.getSize().y / 2) {
		rectangle.setPosition(rectangle.getPosition().x, stage.borderSize * windowSize.y + rectangle.getSize().y / 2);
		return true;
	}
	else if (windowSize.y - stage.borderSize * windowSize.y < rectangle.getPosition().y + rectangle.getSize().y / 2) {
		rectangle.setPosition(rectangle.getPosition().x, windowSize.y - stage.borderSize * windowSize.y - rectangle.getSize().y / 2);
		return true;
	}
	return false;
}

void Player::draw() {
	if (id == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			rectangle.move(0.f, -3.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			rectangle.move(0.f, 3.f);
		}
	}
	else if (id == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			rectangle.move(0.f, -3.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			rectangle.move(0.f, 3.f);
		}
	}
	checkCollision();
	window.draw(rectangle);
}