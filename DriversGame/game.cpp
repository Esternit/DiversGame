#include "game.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "player.h"
#include <map>

using namespace sf;

Game::Game(std::string BGpath, std::string playerPath) : player(playerPath) {
    //setting and loading background
    if (!backgroundTexture.loadFromFile(BGpath)) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }

    GameBackground.setTexture(&backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    GameBackground.setSize(sf::Vector2f(textureSize.x, textureSize.y));
}

void Game::processer() {
    RenderWindow window(VideoMode(1280, 720), "Divers");

    Vector2f velocity;

    Clock frameClock;

    std::map<std::string, int> keyStatuses = { {"A", 0}, {"D", 0}, {"W", 0}, {"S", 0} };

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::A) {
                    keyStatuses["A"] = 1;
                    velocity.x = -100;
                }
                else if (e.key.code == sf::Keyboard::D) {
					keyStatuses["D"] = 1;
                    velocity.x = 100;
                }

                else if (e.key.code == sf::Keyboard::W) {
                    keyStatuses["W"] = 1;
                    velocity.y = -100;
                }
                else if (e.key.code == sf::Keyboard::S) {
					keyStatuses["S"] = 1;
                    velocity.y = 100;
                }

            }
            else if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::A) {
                    keyStatuses["A"] = 0;
                    if (keyStatuses["D"] == 0) {
                         velocity.x = 0;
                    }
					else {
						velocity.x = 100;
					}
                }
                else if (e.key.code == sf::Keyboard::D) {
					keyStatuses["D"] = 0;
					if (keyStatuses["A"] == 0) {
						velocity.x = 0;
					}
                    else {
						velocity.x = -100;
                    }
                }
                else if (e.key.code == sf::Keyboard::W) {
                    keyStatuses["W"] = 0;
                    if (keyStatuses["S"] == 0) {
                        velocity.y = 0;
                    }
                    else {
						velocity.y = 100;
                    }
                }
                else if (e.key.code == sf::Keyboard::S) {
					keyStatuses["S"] = 0;
                    if (keyStatuses["W"] == 0) {
						velocity.y = 0;
                    }
                    else {
						velocity.y = -100;
                    }
                }
            }
        }

        auto deltaTime = frameClock.restart();

        player.move(velocity * deltaTime.asSeconds());

        window.clear();
        window.draw(GameBackground);
        window.draw(player.getSprite());
        window.display();
    }
}