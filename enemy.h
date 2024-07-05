#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

class Enemy
{
public:
    sf::RectangleShape enemy;
    sf::Texture look;
    float attack_speed; // Speed of the bombs
    sf::Texture bombTexture;

    Enemy() : enemy(sf::Vector2f(50, 50)) {}

    void loadTexture(const string &filename)
    {
        if (!look.loadFromFile(filename))
            cout << "Unable to load texture from file: " << filename << endl;
        enemy.setTexture(&look);
    }
};

class Invader : public Enemy
{
public:
    sf::Time time; // 5 seconds
    // static sf::Vector2f v_velocity;
    // static sf::Vector2f h_velocity;
    sf::Vector2f v_velocity;
    sf::Vector2f h_velocity;
    int enemy_lvl;
    bool destroyed = false;
    float screenHeight = 950.0f;
    static Clock clock;   // Clock to control bomb firing rate
    vector<Sprite> bombs; // Vector to hold bomb sprites

    Invader()
    {
        v_velocity = sf::Vector2f(0.0, 0.1);
        h_velocity = sf::Vector2f(0.1, 0.0);
        if (!bombTexture.loadFromFile("img/enemy_laser.png"))
            cout << "Error in loadng bomb texture\n";
    }

    void v_move()
    {
        if ((v_velocity.y > 0 && enemy.getPosition().y + enemy.getSize().y / 2 >= 650) ||
            (v_velocity.y < 0 && enemy.getPosition().y - enemy.getSize().y / 2 <= 100))
            reverse_move_v();

        enemy.move(v_velocity);
    }  
   
    void h_move()
    {

        if ((h_velocity.x > 0 && enemy.getPosition().x + enemy.getSize().x / 2 >= 650) ||
            (h_velocity.x < 0 && enemy.getPosition().x - enemy.getSize().x / 2 <= 50))
            reverse_move_h();
        enemy.move(h_velocity);
    }

    void reverse_move_h()
    {
        h_velocity.x = -h_velocity.x;
    }

    void reverse_move_v()
    {
        v_velocity.y = -v_velocity.y;
    }

    // Function to update the bombs' positions
    void updateBombs(float deltaTime)
    {
        for (size_t i = 0; i < bombs.size(); ++i)
        {
            bombs[i].move(0, attack_speed * deltaTime);

            // Remove bombs that go out of screen
            if (bombs[i].getPosition().y > screenHeight)
            {
                bombs.erase(bombs.begin() + i);
                --i;
            }
        }
    }

    void drawBombs(RenderWindow &window)
    {
        for (const auto &bomb : bombs)
        {
            window.draw(bomb);
        }
    }

    void attack()
    {
        if (clock.getElapsedTime().asSeconds() > time.asSeconds())
        {
            // Create a new bomb sprite
            Sprite bomb(bombTexture);
            bomb.setPosition(enemy.getPosition().x, enemy.getPosition().y + enemy.getSize().y / 2);

            // Add the bomb to the list of bombs
            bombs.push_back(bomb);

            // Restart the clock
            clock.restart();
        }
    }
};

class alpha : public Invader
{
public:
    alpha(int spd)
    {
        loadTexture("img/enemy_1.png");
        enemy_lvl = 1;
        time = sf::seconds(5);
        attack_speed = spd;
    }
};

class beta : public Invader
{
public:
    beta(int spd)
    {
        loadTexture("img/enemy_2.png");
        enemy_lvl = 2;
        time = sf::seconds(3);
        attack_speed = spd;
    }
};

class gamma : public Invader
{
public:
    gamma(int spd)
    {
        loadTexture("img/enemy_3.png");
        enemy_lvl = 3;
        time = sf::seconds(2);
        attack_speed = spd;
    }
};

class Monster : public Enemy
{
public:
    int life;
    void animation();

    void attack(sf::Vector2f pos) {}

    void updateBombs(float deltaTime) {}
};

class Dragon : public Enemy
{
public:
    Clock clock;
    sf::Sprite fire;
    sf::SoundBuffer firebuffer;
    sf::Sound firesound;
    Dragon()
    {

        look.loadFromFile("img/dragon2.png");
        enemy.setTexture(&look);
        enemy.setSize(static_cast<Vector2f>(look.getSize()));
        enemy.setPosition(50, 50);
        bombTexture.loadFromFile("img/flame.png");
        attack_speed = 100.0f;
        fire.setTexture(bombTexture);
        fire.setPosition(350, 540);
        fire.setOrigin(bombTexture.getSize().x / 2, 0);
        firebuffer.loadFromFile("sounds/fire.wav");
        firesound.setBuffer(firebuffer);
    }

    void attack(Vector2f playerPos)
    {
        float x = playerPos.x;
        float y = playerPos.y;

        const float screenWidth = 750;
        const float screenHeight = 950;

        const float bottomHeightBoundary = screenHeight / 3;

        const float leftBoundary = screenWidth / 3;
        const float rightBoundary = 2 * screenWidth / 3;

        if (y >= screenHeight - bottomHeightBoundary)
        {
            if (x < leftBoundary) // Bottom left
            {
                fire.setRotation(45);
            }
            else if (x < rightBoundary) // Bottom mid
            {
                fire.setRotation(0);
            }
            else // Bottom right
            {
                fire.setRotation(-45);
            }
        }
        else
        {
            fire.setRotation(90);
        }
    }
};

Clock Invader::clock;
// sf::Vector2f Invader::v_velocity = sf::Vector2f(0.0, 0.05); Vertical velocity
// sf::Vector2f Invader::h_velocity = sf::Vector2f(0.05, 0.0); Horizontal velocity