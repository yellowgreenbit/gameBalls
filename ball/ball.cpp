//
// Created by Home on 08.02.2022.
//

#include "ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// gravity and other collisions
void Ball::updatePosition(){

    //move by angle
    sf::Vector2f oldPos = sprite.getPosition();
    sf::Vector2f delta;

    if(moveAngle.y > 0) {
        //down
        speed += (speed > maxSpeed) ? 0.0f : gravityVelocity;
        delta.x = moveAngle.x * horizontalFriction;
        delta.y = moveAngle.y * speed;
    } else {
        //up
        speed -= friction;
        delta.x = moveAngle.x * horizontalFriction;
        delta.y = moveAngle.y * speed;

        if(speed < 0){
            if(this -> active){
                // change y direction
                this -> updateDirection('x');
            } else {
                if(this -> active == false){
                    this -> removeMe = true;
                }
            }
        }
    }

    sf::Vector2f newPos = oldPos + delta;
    sprite.setPosition(newPos.x, newPos.y);

    if (
            newPos.x + ballRadius >= WINDOW_WIDTH ||
            newPos.x <= 0
       ) {
        this->updateDirection('y');
    }
}

void Ball::setPosition(sf::Vector2f defaultPos){
    sprite.setPosition(defaultPos.x, defaultPos.y);
}

void Ball::updateDirection(char dimension, float scale, bool changeByCollision){
    speed *= scale;

    if (!collisionDetect){
        switch (dimension) {
            case 'x':
            {
                moveAngle.y *= -1.0f;
                break;
            }
            case 'y':
            {
                moveAngle.x *= -1.0f;
                break;
            }
        }
    }

    this -> collisionDetect = changeByCollision;
}

sf::Sprite Ball::getDrawable() {
    return sprite;
}

Ball::~Ball() {

}