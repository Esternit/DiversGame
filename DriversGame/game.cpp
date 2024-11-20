#include "game.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "player.h"
#include <map>
#include <cstdlib>
#include <random>

#include <ctime>
#include <limits>
#include "Bullet.h"

const float GAME_WIDTH = 2400.f;
const float GAME_HEIGHT = 2400.f;

const std::vector<std::string> rockNames = { "Gold", "Red", "Ultra", "Omega" };
const std::vector<float> probabilities = { 0.3f, 0.4f, 0.2f, 0.1f };

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

    IniFile iniBuffs("Assets/config.ini");
    IniFile iniRocks("Assets/rocks.ini");

    Font font;
    if (!font.loadFromFile("Assets/open-sans/OpenSans-Bold.ttf")) {
         std::cerr << "Error loading font." << std::endl;
    }

    sf::RectangleShape frame1(sf::Vector2f(200, 300));
    sf::RectangleShape frame2(sf::Vector2f(200, 300));
    sf::RectangleShape frame3(sf::Vector2f(200, 300));

    frame1.setFillColor(sf::Color(0, 0, 255, 128));
    frame2.setFillColor(sf::Color(0, 0, 255, 128));
    frame3.setFillColor(sf::Color(0, 0, 255, 128));

    sf::Text text1("Power-Up 1", font, 20);
    sf::Text text2("Power-Up 2", font, 20);
    sf::Text text3("Power-Up 3", font, 20);

    text1.setFillColor(sf::Color::White);
    text2.setFillColor(sf::Color::White);
    text3.setFillColor(sf::Color::White);

    text1.setCharacterSize(14);



    bool powerUpSelected = true;

    //Minotaur Minotaur(TextureHolder::GetTexture("Assets/Enemy/Minotaur.png"), 1280, 720);

    Clock frameClock, animationMovementClock, animateAttackClock, animateMovementEnemyClock, animateAttackEnemyClock, shootClock;

    std::map<std::string, int> keyStatuses = { {"A", 0}, {"D", 0}, {"W", 0}, {"S", 0} };
    View playerView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    bool speedIncrease = false, attack = false;
    int attackFrame = -1;
    std::vector<Bullet> bullets;
    std::vector<Experience> experience;
    std::vector<std::pair<std::string, float>> availableBuffs;

    const float mapWidth = GAME_WIDTH;
    const float mapHeight = GAME_HEIGHT;

    srand((unsigned)time(NULL));

    RectangleShape healthBarBg(sf::Vector2f(200, 20));
    healthBarBg.setPosition(50, 50);
    healthBarBg.setFillColor(sf::Color(50, 50, 50));

    RectangleShape healthBar(sf::Vector2f(200, 20));
    healthBar.setPosition(50, 50);
    healthBar.setFillColor(sf::Color(100, 250, 50));

    RectangleShape experienceBarBg(sf::Vector2f(200, 20));
    experienceBarBg.setPosition(50, 50);
    experienceBarBg.setFillColor(sf::Color(50, 50, 50));

    RectangleShape experienceBar(sf::Vector2f(200, 20));
    experienceBar.setPosition(50, 150);
    experienceBar.setFillColor(sf::Color(50, 150, 250));

    std::vector<Rock> rocks;
    
    spawnRocks(rocks, 10, iniRocks);
    spawnEnemies(100);
    while (window.isOpen())
    {
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            else if (e.type == sf::Event::MouseButtonPressed && !powerUpSelected) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos, playerView);

                if (frame1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    powerUpSelected = true;
                    giveBuff(player, availableBuffs[0]);
                    availableBuffs.clear();
                }
                else if (frame2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    powerUpSelected = true;
                    giveBuff(player, availableBuffs[1]);
                    availableBuffs.clear();
                }
                else if (frame3.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    powerUpSelected = true;
                    giveBuff(player, availableBuffs[2]);
                    availableBuffs.clear();
                }
            }
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

        player.move(velocity * deltaTime.asSeconds(), speedIncrease, mapWidth, mapHeight);

        

        for (auto& bullet : bullets) {
            bullet.move(deltaTime.asSeconds());
        }

        Enemy* closestEnemy = findClosestEnemy(player.getSprite(), player.getGun().getRange());

        

        for (auto& enemy : enemies) {
            Vector2f diractionEnemy = normalize(player.getSprite().getPosition() - enemy.getSprite().getPosition());
            if (!enemy.getAttack()) {
                enemy.move(diractionEnemy * 50.0f * deltaTime.asSeconds(), enemies);
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
                player.setHealth(player.getHealth() - enemy.getDamage());
            }

            if (enemy.getAttack() && enemy.getAnimateAttackClock().getElapsedTime().asSeconds() > 0.1) {
                enemy.animateAttack(diractionEnemy);
                enemy.resetAnimateAttackClock();
            }
        }

		
        if (animationMovementClock.getElapsedTime().asSeconds() > (velocity.x == 0 && velocity.y == 0 ? 0.25 : 0.1) && !attack) {
            animationMovementClock.restart();
            player.animateMovement(velocity);
        }

        if (attack && animateAttackClock.getElapsedTime().asSeconds() > 0.1) {
            if (!player.animateAttack(velocity * deltaTime.asSeconds(), attackFrame)) {
                for (int i = 0; i < rocks.size(); i++) {
                    if (checkCollision(player.getSprite(), rocks[i].getSprite())) {
                        rocks[i].takeDamage(player.getMeleeAttack());
                    }
                }
                attack = false;
            }


			animateAttackClock.restart();
        }

        handlePlayerCollisions(player, rocks);

        rocks.erase(std::remove_if(rocks.begin(), rocks.end(),
            [this](Rock& rock) {
                if (rock.getHealth() <= 0) {
                    player.setGold(player.getGold() + rock.getGivesGold());
                    player.setRed(player.getRed() + rock.getGivesRed());
                    return true;
                }
                return false;
            }), rocks.end());

        if (closestEnemy != nullptr) {
            if (shootClock.getElapsedTime().asSeconds() > player.getGun().getFireRate()) {
                shootClock.restart();
                Vector2f diractionEnemyBullet = normalize(closestEnemy->getSprite().getPosition() - player.getSprite().getPosition());
                bullets.push_back(Bullet(TextureHolder::GetTexture("Assets/Guns/Bullets.png"), player.getGun().getGun().getPosition().x, player.getGun().getGun().getPosition().y, 8, 10, player.getGun().getAttackGamage(), FrameAnimation(180, 0, 130, 0), diractionEnemyBullet));
            }

            bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                [this](const Bullet& bullet) {
                    for (int i = 0; i < enemies.size(); i++) {
                        if (checkCollision(bullet.getSprite(), enemies[i].getSprite())) {
                            enemies[i].updateHealth(bullet.getAttackGamage());
                            return true;
                        }
                    }
                    return false;
                }), bullets.end());
            player.setGunRotation(closestEnemy->getSprite().getPosition());
        }


        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
			[this, &experience](Enemy& enemy) {
                if (enemy.getHealth() <= 0) {
                    spawnExperience(experience, enemy);
                    return true;
                }
				return false;
			}), enemies.end());


		experience.erase(std::remove_if(experience.begin(), experience.end(),
            [this](Experience& experience) {
                if (checkCollision(experience.getSprite(), player.getSprite())) {
                    player.updateExperience(experience.getXpGiven());
                    return true;
                }
				return false;
            }), experience.end());


        Vector2f playerPos = player.getSprite().getPosition();
        Vector2f viewSize = playerView.getSize();
        float halfWidth = viewSize.x / 2.0f;
        float halfHeight = viewSize.y / 2.0f;

        float clampedX = std::max(halfWidth, std::min(playerPos.x, mapWidth - halfWidth));
        float clampedY = std::max(halfHeight, std::min(playerPos.y, mapHeight - halfHeight));

        playerView.setCenter(clampedX, clampedY);

		window.setView(playerView);

        window.clear();
        window.draw(GameBackground);
        for (auto& enemy : enemies) {
            window.draw(enemy.getSprite());
        }
        for (auto& experience : experience) {
            window.draw(experience.getSprite());
        }

        for (auto& rock : rocks) {
            window.draw(rock.getSprite());
        }
        
        window.draw(player.getSprite());
        window.draw(player.getGun().getGun());
        for (auto& bullet : bullets) {
			window.draw(bullet.getSprite());
        }

        Vector2f viewCenter = playerView.getCenter();
        float barX = viewCenter.x - viewSize.x / 2 + 50;
        float barY = viewCenter.y - viewSize.y / 2 + 50;

        healthBarBg.setPosition(barX, barY);
        healthBar.setPosition(barX, barY);

        if (player.getExperience() >= player.getLevel() * 10) {
            player.setLevel(player.getLevel() + 1);
            player.setExperience(0);
            powerUpSelected = false;
        }

        experienceBarBg.setPosition(barX, barY + 30);
		experienceBar.setPosition(barX, barY + 30);

        if (!powerUpSelected) {
            if (availableBuffs.size() == 0) {
                calculateBuffs(iniBuffs, availableBuffs);

                text1.setString(availableBuffs[0].first);
                text2.setString(availableBuffs[1].first);
                text3.setString(availableBuffs[2].first);
            }

            frame1.setPosition(barX + 300, barY + 200);
            frame2.setPosition(barX + 550, barY + 200);
            frame3.setPosition(barX + 800, barY + 200);




            text1.setPosition(
                frame1.getPosition().x + (frame1.getSize().x - text1.getGlobalBounds().width) / 2,
                frame1.getPosition().y + (frame1.getSize().y - text1.getGlobalBounds().height) / 2
            );

            text2.setPosition(
                frame2.getPosition().x + (frame2.getSize().x - text2.getGlobalBounds().width) / 2,
                frame2.getPosition().y + (frame2.getSize().y - text2.getGlobalBounds().height) / 2
            );

            text3.setPosition(
                frame3.getPosition().x + (frame3.getSize().x - text3.getGlobalBounds().width) / 2,
                frame3.getPosition().y + (frame3.getSize().y - text3.getGlobalBounds().height) / 2
            );


            window.draw(frame1);
            window.draw(text1);

            window.draw(frame2);
            window.draw(text2);

            window.draw(frame3);
            window.draw(text3);
        }

        float healthPercent = player.getHealth() / player.getMaxHealth();
        float experiencePercent = player.getExperience() / (player.getLevel() * 10);
        healthBar.setSize(Vector2f(200 * healthPercent, 20));
		experienceBar.setSize(Vector2f(200 * experiencePercent, 20));
        window.draw(healthBarBg);
        window.draw(healthBar);
		window.draw(experienceBarBg);
		window.draw(experienceBar);
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
        enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/firebug.png"), posX, posY, FrameAnimation(0, 90, 0, 100), 65, 40, 20, 3, 2, "Firebug"));
        //enemies.push_back(Enemy(TextureHolder::GetTexture("Assets/Enemy/Minotaur.png"), posX, posY, FrameAnimation(0, 90, 0, 100), 60, 60, 100, 10, 20, "Minotaur"));
    }
}

Enemy* Game::findClosestEnemy(sf::Sprite sprite, float range) {
    Enemy* closestEnemy = nullptr;
    Vector2f diractionEnemy;
    float closestDistance = std::numeric_limits<float>::max();
    for (auto& enemy : enemies) {
        Vector2f direction = sprite.getPosition() - enemy.getSprite().getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < closestDistance && distance < range) {
			closestDistance = distance;
			closestEnemy = &enemy;
        }
    }

	return closestEnemy;
}

void Game::spawnExperience(std::vector<Experience>& experience, Enemy enemy){
    for (int i = 0; i < enemy.getAmountXp(); i++){
        experience.push_back(Experience(TextureHolder::GetTexture("Assets/Effects/Exp.png"), enemy.getGivesXp() / enemy.getAmountXp(), enemy.getSprite().getPosition().x + rand() % 100, enemy.getSprite().getPosition().y + rand() % 100, 7, 7, FrameAnimation(324, 0, 85, 0)));
    }
}

void Game::calculateBuffs(IniFile& ini, std::vector<std::pair<std::string, float>>& availableBuffs) {
    std::vector<std::string> sectionNames = ini.getSectionsNames();
    int sectionAmount = ini.getSectionsCount();
    std::vector<int> indexes;
    for (int i = 0; i < 3; i++) {
        int index = rand() % sectionAmount;
        while (std::find(indexes.begin(), indexes.end(), index) != indexes.end()) {
            index = rand() % sectionAmount;
        }

        std::string name = ini.readString(sectionNames[index], "name");
        std::replace(name.begin(), name.end(), '_', ' ');
        availableBuffs.push_back(std::make_pair(name, ini.readInt(sectionNames[index], "value")));
        indexes.push_back(index);
    }
}

void Game::giveBuff(Player& player, std::pair<std::string, float> buff) {

    if (buff.first == "increase fire rate") {
        player.getGun().setFireRate(player.getGun().getFireRate() * buff.second);
    }
    else if (buff.first == "increase max health") {
        player.setMaxHealth(player.getMaxHealth() * buff.second);
    }
    else if (buff.first == "increase movement speed") {
        player.setSpeed(player.getSpeed() * buff.second);
    }

}

void Game::spawnRocks(std::vector<Rock>& rocks, int numRocks, IniFile& ini) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < numRocks; ++i) {
        Rock rock = chooseRock(ini);

        //Rock rock(TextureHolder::GetTexture("Assets/Mining/64x64/" + name + "1.png"), 1, 1, name);

        float rockWidth = rock.getSprite().getGlobalBounds().width;
        float rockHeight = rock.getSprite().getGlobalBounds().height;

        float x = std::rand() % static_cast<int>(GAME_WIDTH - rockWidth);
        float y = std::rand() % static_cast<int>(GAME_HEIGHT - rockHeight);

        rock.setPosition(x, y);

        bool valid = true;
        for (const auto& otherRock : rocks) {
            if (checkCollision(rock.getSprite(), otherRock.getSprite())) {
                valid = false;
                break;
            }
        }

        if (valid) {
            rocks.push_back(rock);
        }
        else {
            --i;
        }
    }
}

Rock Game::chooseRock(IniFile& ini) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    float randomValue = dis(gen);

    float cumulativeProbability = 0.0f;
    for (size_t i = 0; i < rockNames.size(); ++i) {
        cumulativeProbability += probabilities[i];
        if (randomValue <= cumulativeProbability) {
            return Rock(TextureHolder::GetTexture("Assets/Mining/64x64/" + rockNames[i] + "1.png"), 1, 1, rockNames[i], ini.readInt(rockNames[i], "health"), ini.readInt(rockNames[i], "givesGold"), ini.readInt(rockNames[i], "givesRed"));
        }
    }

    return Rock(TextureHolder::GetTexture("Assets/Mining/64x64/" + rockNames.back() + "1.png"), 1, 1, rockNames.back(), ini.readInt(rockNames.back(), "health"), ini.readInt(rockNames.back(), "givesGold"), ini.readInt(rockNames.back(), "givesRed"));
}

void Game::handlePlayerCollisions(Player& player, const std::vector<Rock>& rocks) {
    for (const auto& rock : rocks) {
        if (checkCollision(player.getSprite(), rock.getSprite())) {
            sf::FloatRect intersection;
            if (player.getSprite().getGlobalBounds().intersects(rock.getSprite().getGlobalBounds(), intersection)) {
                if (intersection.width > intersection.height) {

                    if (player.getSprite().getPosition().y < rock.getSprite().getPosition().y) {
                        player.moveAlone(0, -intersection.height);
                    }
                    else {
                        player.moveAlone(0, intersection.height);
                    }
                }
                else {
                    if (player.getSprite().getPosition().x < rock.getSprite().getPosition().x) {
                        player.moveAlone(-intersection.width, 0);
                    }
                    else {
                        player.moveAlone(intersection.width, 0);
                    }
                }
            }
        }
    }
}
