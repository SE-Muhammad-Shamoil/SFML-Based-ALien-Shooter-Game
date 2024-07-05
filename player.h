#include <SFML/Graphics.hpp>
#include <vector>
#include "bullet.h"

class SpaceShip
{
private:
    sf::Clock fireClock; // Clock to track the time since the last bullet was fired
    sf::Clock clock;
    sf::Clock shield_clock;
    sf::Texture pl_tex;
    sf::Texture shield_tex;
    sf::Texture tex;
    sf::Texture bull_tex;
    bool canFire = true; // Flag to track whether the player can fire a bullet(to force a time gap)

public:
    std::vector<Bullet> bullets; // Vector to hold bullets fired by the player
    sf::Sprite pl_lives; //Lives display
    sf::Sprite sprite;
    sf::Sprite shield_sh;
    int life; //Lives left
    float speed = 0.5;
    float fireRate = 0.2f; // Fire rate in seconds
    bool shield = false;
    bool took_damage = false;

    SpaceShip(std::string png_path = "img/PNG/playerShip2_orange")
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(375, 900);
        sprite.setScale(0.75, 0.75);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        life = 3;
        bull_tex.loadFromFile("img/PNG/Lasers/laserBlue01.png");
        pl_tex.loadFromFile("img/PNG/UI/playerLife2_orange.png");
        pl_lives.setTexture(pl_tex);
        shield_tex.loadFromFile("img/shield_bubble.png");
        shield_sh.setTexture(shield_tex);
        shield_sh.setOrigin(shield_sh.getLocalBounds().height / 2, shield_sh.getLocalBounds().width / 2);
        shield_sh.setColor(sf::Color::Transparent);
    }

    void move(const std::string &input)
    {
        float delta_x = 0, delta_y = 0;
        float rotation = 0;

        if (input == "w" && delta_y > (-sprite.getLocalBounds().height / 2))
        {
            delta_y = -1;
        }
        else if (input == "s" && delta_y < (1000 - sprite.getLocalBounds().height))
        {
            delta_y = 1;
        }
        else if (input == "a")
        {
            delta_x = -1;
            rotation = -20.0f;
        }
        else if (input == "d")
        {
            delta_x = 1;
            rotation = 20.0f;
        }

        delta_x *= speed;
        delta_y *= speed;

        sprite.move(delta_x, delta_y);
        sprite.setRotation(rotation);
        wrap_check();
    }

    void damagecheck()
    {
        if (took_damage == true && sprite.getColor() != sf::Color::Red)
        {
            clock.restart();
            sprite.setColor(sf::Color::Red);
            setshield();
        }

        if (took_damage == true && sprite.getColor() == sf::Color::Red && clock.getElapsedTime() > sf::seconds(0.5))
        {
            sprite.setColor(sf::Color::White);
            took_damage = false; 
        }
    }

    void shieldcheck()
    {
        if (shield == true)
        {
            shield_sh.setColor(sf::Color::White);
            shield_sh.setPosition(sprite.getPosition());
        }

        if (shield == true && shield_clock.getElapsedTime() > sf::seconds(2))
        {
            shield = false; 
            shield_sh.setColor(sf::Color::Transparent);
        }
    }

    void fireBullet()
    {
        if (canFire)
        {
            sf::Vector2f bulletPosition = sprite.getPosition() - sf::Vector2f(0, sprite.getLocalBounds().height / 2);
            bullets.emplace_back(bull_tex, bulletPosition);

            fireClock.restart();

            // Prevent the player from firing for the duration of the fire rate
            canFire = false;
        }
    }

    void updateBullets()
    {
        if (!canFire && fireClock.getElapsedTime().asSeconds() >= fireRate)
        {
            canFire = true; // Allow the player to fire again
        }

        for (size_t i = 0; i < bullets.size(); ++i)
        {
            // Move bullets upwards
            bullets[i].move(0, -2);

            // Remove bullets when they go out of screen
            if (bullets[i].getPosition().y < 0)
            {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }
    }

    void drawBullets(sf::RenderWindow &window)
    {
        for (const auto &bullet : bullets)
        {
            window.draw(bullet.sprite);
        }
    }

    void drawlives(sf::RenderWindow &window)
    {
        if (life > 0)
        {
            pl_lives.setPosition(690, 20);
            window.draw(pl_lives);
        }
        if (life > 1)
        {
            pl_lives.setPosition(650, 20);
            window.draw(pl_lives);
        }
        if (life > 2)
        {
            pl_lives.setPosition(610, 20);
            window.draw(pl_lives);
        }
    }

    void setshield()
    {
        shield = true;
        shield_clock.restart();
    }

    void wrap_check()
    {
        sf::Vector2f position = sprite.getPosition();
        if (position.x < 0)
        {
            position.x = 700; 
        }
        else if (position.x > 700)
        {
            position.x = 0;
        }

        if (position.y < 0)
        {
            position.y = 950; 
        }
        else if (position.y > 950)
        {
            position.y = 0;
        }

        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow &window) //To draw all feauture of player and lives
    {
        window.draw(shield_sh);
        window.draw(sprite);
        drawBullets(window);  
        drawlives(window);
    }
};
