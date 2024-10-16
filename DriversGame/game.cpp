#include "game.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "player.h"
#include <map>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <limits>
#include "Minotaur.h"
#include "Bullet.h"


using namespace sf;

Game::Game(std::string BGpath, std::string playerPath) :  player(TextureHolder::GetTexture(playerPath), 100, 2, TextureHolder::GetTexture("Assets/Guns/tier-1.png")) {
    //setting and loading background

    GameBackground.setTexture(&TextureHolder::GetTexture(BGpath));

    sf::Vector2u textureSize = TextureHolder::GetTexture(BGpath).getSize();
    GameBackground.setSize(sf::Vector2f(textureSize.x, textureSize.y));
}

void Game::processer() {
    RenderWindow window(VideoMode(1280, 720), "Divers");

    Vector2f velocity;

    //Minotaur Minotaur(TextureHolder::GetTexture("Assets/Enemy/Minotaur.png"), 1280, 720);

    Clock frameClock, animationMovementClock, animateAttackClock, animateMovementEnemyClock, animateAttackEnemyClock, shootClock;

    std::map<std::string, int> keyStatuses = { {"A", 0}, {"D", 0}, {"W", 0}, {"S", 0} };
    View playerView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    bool speedIncrease = false, attack = false;
    int attackFrame = -1;
    std::vector<Bullet> bullets;
    
    spawnEnemies(3);
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
                    velocity.x = -player.getSpeed();
                }
                else if (e.key.code == sf::Keyboard::D) {
					keyStatuses["D"] = 1;
                    velocity.x = player.getSpeed();
                }

                else if (e.key.code == sf::Keyboard::W) {
                    keyStatuses["W"] = 1;
                    velocity.y = -player.getSpeed();
                }
                else if (e.key.code == sf::Keyboard::S) {
					keyStatuses["S"] = 1;
                    velocity.y = player.getSpeed();
                }
                else if (e.key.code == sf::Keyboard::E) {
					attack = true;
                    srand(time(0));
                    attackFrame = rand() % 3;
                }
                else if (e.key.code == sf::Keyboard::LShift) {
					speedIncrease = true;
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
						velocity.x = player.getSpeed();
					}
                }
                else if (e.key.code == sf::Keyboard::D) {
					keyStatuses["D"] = 0;
					if (keyStatuses["A"] == 0) {
						velocity.x = 0;
					}
                    else {
						velocity.x = -player.getSpeed();
                    }
                }
                else if (e.key.code == sf::Keyboard::W) {
                    keyStatuses["W"] = 0;
                    if (keyStatuses["S"] == 0) {
                        velocity.y = 0;
                    }
                    else {
						velocity.y = player.getSpeed();
                    }
                }
                else if (e.key.code == sf::Keyboard::S) {
					keyStatuses["S"] = 0;
                    if (keyStatuses["W"] == 0) {
						velocity.y = 0;
                    }
                    else {
						velocity.y = -player.getSpeed();
                    }
                }
				else if (e.key.code == sf::Keyboard::LShift) {
					speedIncrease = false;
				}
            }
        }

        auto deltaTime = frameClock.restart();

        player.move(velocity * deltaTime.asSeconds(), speedIncrease);

        for (auto& bullet : bullets) {
            bullet.move(deltaTime.asSeconds());
        }

        Enemy* closestEnemy = findClosestEnemy(player.getSprite());

        

        for (auto& enemy : enemies) {
            Vector2f diractionEnemy = normalize(player.getSprite().getPosition() - enemy.getSprite().getPosition());
            if (!enemy.getAttack()) {
                enemy.move(diractionEnemy * 50.0f * deltaTime.asSeconds());
            }

            if (enemy.getAnimateMovementClock().getElapsedTime().asSeconds() > 0.15 && !enemy.getAttack()) {

                enemy.resetAnimateMovementClock();
                enemy.animateMovement(diractionEnemy);
            }

            FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();

            enemyBounds.width -= diractionEnemy.x < 0 ? 20 : 50;
            enemyBounds.height -= 20;

            if (enemyBounds.intersects(player.getSprite().getGlobalBounds()) && !enemy.getAttack()) {
                enemy.setAttack(true);
            }

            if (enemy.getAttack() && enemy.getAnimateAttackClock().getElapsedTime().asSeconds() > 0.1) {
                enemy.animateAttack(diractionEnemy);
                enemy.resetAnimateAttackClock();
            }
        }

        //if (!Minotaur.getAttack()) {
        //    Minotaur.move(diractionEnemy * 50.0f * deltaTime.asSeconds());
        //}
		
        if (animationMovementClock.getElapsedTime().asSeconds() > (velocity.x == 0 && velocity.y == 0 ? 0.25 : 0.1) && !attack) {
            animationMovementClock.restart();
            player.animateMovement(velocity);
        }
   //     if (animateMovementEnemyClock.getElapsedTime().asSeconds() > 0.15 && !Minotaur.getAttack()) {
   //         
			//animateMovementEnemyClock.restart();
   //         Minotaur.animateMovement(diractionEnemy);
   //     }
        if (attack && animateAttackClock.getElapsedTime().asSeconds() > 0.1) {
            if (!player.animateAttack(velocity * deltaTime.asSeconds(), attackFrame)) {
                attack = false;
            }
			animateAttackClock.restart();
        }
   //     FloatRect minotaurBounds = Minotaur.getSprite().getGlobalBounds();

   //     minotaurBounds.width -= diractionEnemy.x < 0 ? 20 : 50; 
   //     minotaurBounds.height -= 20; 

   //     if (minotaurBounds.intersects(player.getSprite().getGlobalBounds()) && !Minotaur.getAttack()) {
   //         Minotaur.setAttack(true);
   //     }

   //     if (Minotaur.getAttack() && animateAttackClock.getElapsedTime().asSeconds() > 0.1) {
   //         Minotaur.animateAttack(diractionEnemy);
			//animateAttackClock.restart();
   //     }

        if (shootClock.getElapsedTime().asSeconds() > player.getGun().getFireRate()) {
			shootClock.restart();
            Vector2f diractionEnemyBullet = normalize(closestEnemy->getSprite().getPosition() - player.getSprite().getPosition());
            bullets.push_back(Bullet(TextureHolder::GetTexture("Assets/Guns/Bullets.png"), player.getGun().getGun().getPosition().x, player.getGun().getGun().getPosition().y, 8, 10, player.getGun().getAttackGamage(), FrameAnimation(180, 0, 130, 0), diractionEnemyBullet));
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [this, &closestEnemy](const Bullet& bullet) {
                if (checkCollision(bullet.getSprite(), closestEnemy->getSprite())) {
                    closestEnemy->updateHealth(bullet.getAttackGamage());
                    std::cout << closestEnemy->getHealth() << std::endl;
                    return true;
                }
                return false;
            }), bullets.end());
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
			[this](Enemy& enemy) {
				return enemy.getHealth() <= 0;
			}), enemies.end());


		playerView.setCenter(player.getSprite().getPosition());

        player.setGunRotation(closestEnemy->getSprite().getPosition());

		window.setView(playerView);

        window.clear();
        window.draw(GameBackground);
        for(auto& enemy : enemies) {
			window.draw(enemy.getSprite());
		}
        //window.draw(Minotaur.getSprite());
        window.draw(player.getSprite());
        window.draw(player.getGun().getGun());
        for (auto& bullet : bullets) {
			window.draw(bullet.getSprite());
        }
        window.display();
    }
}

Vector2f Game::normalize(const sf::Vector2f& source) {
    float length = std::sqrt(source.x * source.x + source.y * source.y);
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

bool Game::checkCollision(const sf::Sprite& rect1, const sf::Sprite& rect2) {
    return rect1.getGlobalBounds().intersects(rect2.getGlobalBounds());
}

void Game::spawnEnemies(int amount) {
    int posX, posY;
    for (int i = 0; i < amount; i++) {
        posX = rand() % 2401;
        posY = rand() % 1441;
        enemies.push_back(Minotaur(TextureHolder::GetTexture("Assets/Enemy/Minotaur.png"), posX, posY));
    }
}

Enemy* Game::findClosestEnemy(sf::Sprite sprite) {
    Enemy* closestEnemy = nullptr;
    Vector2f diractionEnemy;
    float closestDistance = std::numeric_limits<float>::max();
    for (auto& enemy : enemies) {
        Vector2f direction = sprite.getPosition() - enemy.getSprite().getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < closestDistance) {
			closestDistance = distance;
			closestEnemy = &enemy;
        }
    }

	return closestEnemy;
}