//
// Created by Home on 10.02.2022.
//

#include <SFML/Graphics.hpp>

#ifndef HELLOSFML_PLATFORM_H
#define HELLOSFML_PLATFORM_H

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;

class Platform {
public:
    sf::RectangleShape rect;
    sf::Texture texture;
    Platform(){
        rect = sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));
        rect.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT - 120.0);
        texture.loadFromFile("resource/platform.png");
        rect.setTexture(&texture);
    }

    void moveTo(sf::Vector2f);
};


#endif //HELLOSFML_PLATFORM_H
