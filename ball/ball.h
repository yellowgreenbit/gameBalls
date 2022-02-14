//
// Created by Home on 08.02.2022.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "../resourceHolder/ResourceHolder.hpp"

#ifndef HELLOSFML_BALL_H
#define HELLOSFML_BALL_H

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int FRAME_LIMIT;

class Ball {

private:
    float maxSpeed = 1000.0f/ FRAME_LIMIT;
    float gravityVelocity = 35.0f / FRAME_LIMIT;
    float friction = 40.0f / FRAME_LIMIT;
    float horizontalFriction = 500.0f / FRAME_LIMIT;
    float ballRadius = 94.0;
    bool collisionDetect = false; // fix collision gluks

public:
    float speed = 30.0f / FRAME_LIMIT * 2;
    bool active = true;
    bool removeMe = false;
    float ballTouches = 0;
    sf::Sprite sprite;
    sf::Vector2f moveAngle;

    Ball(sf::Vector2f default_pos, sf::Vector2f moveDir, sf::Texture &ballTexture) {
        sprite.setTexture(ballTexture);
        setPosition(default_pos);
        moveAngle = moveDir;
    }

    void updatePosition();

    void setPosition(sf::Vector2f);

    void updateDirection(char dimension, float scale = 1.0f, bool changeByCollision = false);

    sf::Sprite getDrawable();

    // todo destroy

    ~Ball();
};

#endif //HELLOSFML_BALL_H
