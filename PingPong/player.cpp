#include "player.h"

Player::Player(sf::RenderWindow &window_, float vsize_, float spacing_, PlayerID id_, Stage &stage_, Irctwitch &irc_,
               int score_)
    : window{window_}, vsize{vsize_}, spacing{spacing_}, id{id_}, stage{stage_}, irc{irc_} {
    sf::Vector2u windowSize = window.getSize();
    rectangle = sf::RectangleShape(sf::Vector2f(hsize * windowSize.x, vsize * windowSize.y));
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
    if (id == PlayerID::Zero) {
        rectangle.setPosition(windowSize.x * spacing, windowSize.y / 2);
        rectangle.setFillColor(sf::Color::Blue);
    } else if (id == PlayerID::One) {
        rectangle.setPosition(windowSize.x - windowSize.x * spacing, windowSize.y / 2);
        rectangle.setFillColor(sf::Color::Red);
    }
};

bool Player::checkCollision() {
    sf::Vector2u windowSize = window.getSize();
    if (stage.borderSize * windowSize.y > rectangle.getPosition().y - rectangle.getSize().y / 2) {
        rectangle.setPosition(rectangle.getPosition().x, stage.borderSize * windowSize.y + rectangle.getSize().y / 2);
        return true;
    } else if (windowSize.y - stage.borderSize * windowSize.y < rectangle.getPosition().y + rectangle.getSize().y / 2) {
        rectangle.setPosition(rectangle.getPosition().x,
                              windowSize.y - stage.borderSize * windowSize.y - rectangle.getSize().y / 2);
        return true;
    }
    return false;
}

/* TODO: the unordered set "users" still needs to be configured, there should be
a voting phase before the game starts (e.g. a command !team in twitch chat to 
set your team)
*/ 

void Player::draw() {
    if (this->irc.lines.empty())
        return;
    std::tuple<std::string, std::string> command = this->irc.lines.front();
    this->irc.lines.pop();
    if (users.find(std::get<0>(command)) == users.end())
        return;
    
    if (id == PlayerID::Zero) {
        if (std::get<1>(command) == "up") {
            rectangle.move(0.f, -6.f);
        } else if (std::get<1>(command) == "down") {
            rectangle.move(0.f, 6.f);
        }
    } else if (id == PlayerID::One) {
        if (std::get<1>(command) == "up") {
            rectangle.move(0.f, -6.f);
        } else if (std::get<1>(command) == "down") {
            rectangle.move(0.f, 6.f);
        }
    }
    checkCollision();
    window.draw(rectangle);
}
