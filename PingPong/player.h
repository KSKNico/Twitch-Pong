#pragma once
#include "irctwitch.h"
#include "stage.h"

#include <SFML/Graphics.hpp>
#ifndef _PLAYER
#    define _PLAYER

enum class PlayerID {Zero, One};

class Player {
  private:
    float vsize;
    float hsize = 0.03f;
    float spacing;
    Irctwitch &irc;
    PlayerID id;
    Stage stage;
    sf::RenderWindow &window;

  public:
    sf::RectangleShape rectangle;
    int score;
    Player(sf::RenderWindow &window_, float vsize_, float spacing_, PlayerID id_, Stage &stage_, Irctwitch &irc_,
           int score_ = 0);

    bool checkCollision();

    void draw();
};

#endif
