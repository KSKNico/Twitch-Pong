#pragma once
#include "player.h"
#include "stage.h"

#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.1415926
#ifndef _BALL
#    define _BALL

void rotateVector(sf::Vector2f &v, float angle, bool degrees);

class Ball {
  private:
    sf::RenderWindow &window;
    float size;
    sf::Vector2f speed;
    sf::CircleShape circle;
    Stage &stage;
    Player &player1;
    Player &player2;

  public:
    Ball(sf::RenderWindow &window_, float size_, sf::Vector2f speed_, Stage &stage_, Player &player1_,
         Player &player2_);

    bool checkCollision();

    bool collisionBallAndPlayer(Player &player);

    void draw();
};

#endif