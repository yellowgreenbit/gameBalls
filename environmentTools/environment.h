//
// Created by Home on 08.02.2022.
//

#include <SFML/Graphics.hpp>

#ifndef HELLOSFML_ENVIRONMENT_H
#define HELLOSFML_ENVIRONMENT_H

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;

class Environment {
public:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Sprite frontSprite;
    sf::Texture frontTexture;
    Environment(){
        rect = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, 80.0f));
        rect.setPosition(0, WINDOW_HEIGHT - 80.0);
        texture.loadFromFile("resource/grass.png");
        rect.setTexture(&texture);

        backgroundTexture.loadFromFile("resource/back.png");
        backgroundSprite.setTexture(backgroundTexture);

        frontTexture.loadFromFile("resource/front.png");
        frontSprite.setTexture(frontTexture);
        frontSprite.setPosition(0, WINDOW_HEIGHT - 124.0);
    }
};


#endif //HELLOSFML_ENVIRONMENT_H
