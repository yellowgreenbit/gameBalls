#include <SFML/Graphics.hpp>
#include "ball/ball.h"
#include "environmentTools/environment.h"
#include "platform/platform.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FRAME_LIMIT = 60;
const int PLATFORM_SPEED = 500;
float NEW_BALLS_INTERVAL = 2;
const float MIN_BALLS_INTERVAL = 0.02;
const float HARD_DELTA = 0.1f;
const int POS_BALLS_DELTA_X = 100;

/*
 * Textures
 * */
namespace Textures
{
    enum ID
    {
        Ball
    };
}

/*
 * Random-range generator
 * */
float randFloatRange(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

/*
 * Generate and push te ball to balls_arr
 * */
void pushTheBall(std::vector<Ball> &balls_arr, sf::Texture &ballTexture)
{
    float ballPosX = randFloatRange(POS_BALLS_DELTA_X, WINDOW_WIDTH - POS_BALLS_DELTA_X);
    float directionX = randFloatRange(0, .5f) * ((ballPosX > WINDOW_WIDTH / 2) ? -1.0 : 1.0);

    balls_arr.push_back( Ball (
        sf::Vector2f(ballPosX, -100.0),
        sf::Vector2f(directionX, abs(1 - directionX)),
        ballTexture
        )
    );

    NEW_BALLS_INTERVAL -= (NEW_BALLS_INTERVAL - HARD_DELTA > MIN_BALLS_INTERVAL) ? HARD_DELTA : 0;
}

int main()
{
    // WINDOW SETTINGS
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ball!");
    window.setFramerateLimit(FRAME_LIMIT);
    window.setVerticalSyncEnabled(true);

    //PLAYER VARS
    int score = 0;

    //set time begin game
    sf::Clock gameClock;
    sf::Time elapsed1 = gameClock.getElapsedTime();
    std::cout << elapsed1.asSeconds() << "Game start" << std::endl;

    //set balls timer
    sf::Clock ballClock;

    // INIT UI
    sf::Font font;
    sf::Text counter;
    if (!font.loadFromFile("resource/arial.ttf"))
    {
        std::cout << "font load error!";
    } else {
        counter.setFont(font);
        counter.setCharacterSize(48);
        counter.setFillColor(sf::Color::Black);
        counter.setString("Score: " + std::to_string(score));
        counter.setPosition(WINDOW_WIDTH - 250.0f, 50.f);
    }

    // INIT GAME OBJECTS
    Environment environment;
    Platform platform;

    ResourceHolder<sf::Texture, Textures::ID> textures;

    // Try to load resources
    try
    {
        textures.load(Textures::Ball, "resource/ball.png");
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    sf::Texture ballTexture = textures.get(Textures::Ball);

    // Add dinamically ball
    std::vector<Ball> balls_arr;
    pushTheBall(balls_arr, ballTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // CLOSE EVENT
            if (
                    event.type == sf::Event::Closed ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
            ){
                window.close();
                // time end game
                sf::Time elapsed2 = gameClock.getElapsedTime();
                std::cout << elapsed2.asSeconds() << "Game end" << std::endl;
            }
        }

        // KEYBOARD EVENTS
        if(event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left:{
                    platform.moveTo(sf::Vector2f(-PLATFORM_SPEED / FRAME_LIMIT, 0.f));
                    break;
                }
                case sf::Keyboard::Right:{
                    platform.moveTo(sf::Vector2f(PLATFORM_SPEED / FRAME_LIMIT, 0.f));
                    break;
                }
            }
        }

        // TIME-DEPEND EVENT generate ball
        if(int(ballClock.getElapsedTime().asSeconds()) > NEW_BALLS_INTERVAL ) {
            pushTheBall(balls_arr, ballTexture);
            ballClock.restart();
        }

        // CHECK INTERSECTIONS AND UPDATE BALLS POSITIONS
        sf::FloatRect platformBB = platform.rect.getGlobalBounds();
        sf::FloatRect groundBB = environment.rect.getGlobalBounds();

        for ( int i = 0; i < balls_arr.size(); i++ ){
            if(balls_arr[i].active){
                sf::FloatRect ballBB = balls_arr[i].sprite.getGlobalBounds();

                if (ballBB.intersects(platformBB)){
                    //intersect platform
                    score++;
                    counter.setString("Score: " + std::to_string(score));

                    balls_arr[i].updateDirection('x', 1.0f, true);

                    if(++balls_arr[i].ballTouches == 3){
                        balls_arr[i].active = false;
                    }
                }

                if (ballBB.intersects(groundBB)){
                    score -= abs(3 - balls_arr[i].ballTouches);
                    counter.setString("Score: " + std::to_string(score));
                    balls_arr[i].updateDirection('x', .9f, true);
                    balls_arr[i].active = false;
                }
            } else {
                if(balls_arr[i].removeMe){
                    balls_arr.erase(balls_arr.begin() + i);
                    continue;
                }
            }

            balls_arr[i].updatePosition();
        }

        // RENDER
        window.clear(sf::Color::White);
        window.draw(environment.backgroundSprite);

        for ( int i = 0; i < balls_arr.size(); i++ ){
            window.draw(balls_arr[i].getDrawable());
        }

        window.draw(environment.rect);
        window.draw(platform.rect);
        window.draw(environment.frontSprite);
        window.draw(counter);

        window.display();

    }

    return 0;
}
