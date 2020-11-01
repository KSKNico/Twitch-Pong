#pragma once
#include "irctwitch.h"
#include "stage.h"
#include <unordered_set>

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
    std::unordered_set<std::string> users;
    int score;
    Player(sf::RenderWindow &window_, float vsize_, float spacing_, PlayerID id_, Stage &stage_, Irctwitch &irc_,
           int score_ = 0);
    
    bool checkCollision();

    void draw();
};

#endif
