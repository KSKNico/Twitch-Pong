#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ball.h"
#include "stage.h"
#include "player.h"
#include "irctwitch.h"
#include <iostream>

int main() {
	Irctwitch irc("arxl5i3cidzus6w6cxp20dltk3mmt0", "ksk_nico");

	// Needs to be added: sf::Style::Fullscreen
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Ping Pong", sf::Style::Close);
	window.setFramerateLimit(60);
	Stage stage(window, 0.05f);
	Player player1(window, 0.2f, 0.05f, 0, stage, irc);
	Player player2(window, 0.2f, 0.05f, 1, stage, irc);
	Ball ball(window, 20.f, sf::Vector2f(-5.f, -5.f), stage, player1, player2);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		stage.draw();
		player1.draw();
		player2.draw();
		ball.draw();
		window.display();
		if (irc.lines.empty() == false) {
			auto t = irc.lines.front();
			std::cout << std::get<0>(t) << "\t" << std::get<1>(t) << std::endl;
			irc.lines.pop();
		}	
	}
	return 0;
}