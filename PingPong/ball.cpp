#include "ball.h"

void rotateVector(sf::Vector2f &v, float angle, bool degrees = true) {
	if (degrees) {
		angle = angle * PI / 180.f;
	}

	v.x = v.x * cos(angle) - v.y * sin(angle);
	v.y = v.x * sin(angle) + v.y * cos(angle);
}

Ball::Ball(sf::RenderWindow &window_, float size_, sf::Vector2f speed_, Stage &stage_, Player &player1_, Player &player2_) : window{ window_ }, size{ size_ }, speed{ speed_ } ,
	player1{player1_}, player2{player2_}, stage{stage_} 
{
	circle = sf::CircleShape(size);
	circle.setOrigin(circle.getRadius() / 2.f, circle.getRadius() / 2.f);
	circle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

bool Ball::checkCollision() {
	//collision with the left/right goal
	if (circle.getPosition().x < 0) {
		// score player 1
		player1.score += 1;
		// reset ball
		circle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	}
	if (circle.getPosition().x > window.getSize().x) {
		// score player 2
		player2.score += 1;
		// reset ball
		circle.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	}


	//collision top and bottom
	if (circle.getPosition().y - circle.getRadius() + 5 < stage.borderSize * window.getSize().y) {
		speed.y = -speed.y;
		return true;
	}
	if (circle.getPosition().y + circle.getRadius() > window.getSize().y - stage.borderSize * window.getSize().y) {
		speed.y = -speed.y;
		return true;
	}

	//collision with the players
	if (collisionBallAndPlayer(player1)) {
		float dist = player1.rectangle.getPosition().y - circle.getPosition().y;
		float percentage = dist / player1.rectangle.getPosition().y * 2;
		speed.x = -speed.x;
		return true;
	}
	else if (collisionBallAndPlayer(player2))
	{
		float dist = player2.rectangle.getPosition().y - circle.getPosition().y;
		float percentage = dist / player2.rectangle.getPosition().y * 2;
		speed.x = -speed.x;
		rotateVector(speed, percentage * 45.f);
		return true;
	}
	return false;
}

bool Ball::collisionBallAndPlayer(Player &player) {
	sf::Vector2f rectanglePosition = player.rectangle.getPosition();
	float corner_x = player.rectangle.getPosition().x - player.rectangle.getSize().x / 2;
	float corner_y = player.rectangle.getPosition().y - player.rectangle.getSize().y / 2;

	float testX = circle.getPosition().x;
	float testY = circle.getPosition().y;

	if (circle.getPosition().x < corner_x)
		testX = corner_x;
	else if (circle.getPosition().x > player.rectangle.getSize().x + corner_x)
		testX = corner_x + player.rectangle.getSize().x;

	if (circle.getPosition().y < corner_y)
		testY = corner_y;
	else if (circle.getPosition().y > corner_y + player.rectangle.getSize().y)
		testY = corner_y + player.rectangle.getSize().y;

	float distX = circle.getPosition().x - testX;
	float distY = circle.getPosition().y - testY;
	float distance = sqrt((distX*distX) + (distY*distY));
	if (distance <= circle.getRadius()) {
		return true;
	}
	return false;
}

void Ball::draw() {
	circle.move(speed.x, speed.y);
	checkCollision();
	window.draw(circle);
}


