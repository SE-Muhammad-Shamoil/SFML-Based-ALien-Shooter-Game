#include "enemy.h"
#include "addons.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "player.h"

class level
{
protected:
    Invader **eship_ptr;
    Dragon drago;
    Monster ninetails;
    sf::RectangleShape background1;
    sf::RectangleShape background2;
    sf::Texture Background;
    int lvl_no;
    int attack_select;
    int enemy_number;
    int randomizer;
    static sf::Clock dragon_clock;
    int drago_interval;
    sf::RectangleShape danger;
    sf::Texture danger_tex;
    sf::Font lvl_font;
    sf::Text lvl_txt;

public:
    int selector;
    void Animation();
    void draw(sf::RenderWindow &window, float deltaTime);
    void updt(float deltaTime, SpaceShip *player);
    void checkEnemyBulletCollision(SpaceShip *player, int &kill_no, int &score);
    void checkEnemyPlayerCollision(SpaceShip *player, int &kill_no, int &score);
    void checkBombPlayerCollision(SpaceShip *player);
    void lvl_run(sf::RenderWindow &window, SpaceShip *p, int &enemies_destroyed, int &score, float deltaTime, bool pause_check);
    virtual void Shapes() = 0;
    void updateBombs(float deltaTime);
    void mangekyou_updt();
    bool dragon_show(sf::RenderWindow &window);
    bool drago_check;
    static bool mangekyou_status;
    sf::SoundBuffer musicbuff;
    sf::Sound music;
    sf::RectangleShape mangekyou;
    sf::Texture mangekyou_tex;
    Clock mangekyou_clock;
    SoundBuffer mangekyou_buff;
    Sound mangekyou_sound;

    level() : background1(sf::Vector2f(750, 950)), background2(sf::Vector2f(750, 950)), danger(sf::Vector2f(750, 950)), mangekyou(sf::Vector2f(800, 600))
    {

        dragon_clock.restart();
        srand(time(NULL));
        selector = rand() % 3 + 1;
        attack_select = rand() % 19;
        eship_ptr = nullptr;
        drago_interval = rand() % 35 + 15;
        background1.setPosition(0, 0);
        background2.setPosition(Background.getSize().x, 0);
        musicbuff.loadFromFile("sounds/music.wav");
        music.setBuffer(musicbuff);
        danger_tex.loadFromFile("img/danger.png");
        danger.setTexture(&danger_tex);
        mangekyou_tex.loadFromFile("img/mangekyou.png");
        mangekyou.setTexture(&mangekyou_tex);
        mangekyou_tex.setSmooth(true);
        mangekyou.setOrigin(400, 300);
        mangekyou.setPosition(375, 375);
        mangekyou.setScale(50, 50);
        mangekyou_buff.loadFromFile("sounds/mangekyou.wav");
        mangekyou_sound.setBuffer(mangekyou_buff);
        lvl_font.loadFromFile("Welcome_font.otf");
        lvl_txt.setFont(lvl_font);
        lvl_txt.setPosition(20,900);
    }

    void drawbg(sf::RenderWindow &window, float deltaTime)
    {
        static float backgroundOffset = 0.0f; 

        backgroundOffset += 50.0f * deltaTime;

        if (backgroundOffset >= Background.getSize().x)
        {
            backgroundOffset -= Background.getSize().x;
        }

        background1.setPosition(0, -backgroundOffset);
        background2.setPosition(0, Background.getSize().x - backgroundOffset);

        window.draw(background1);
        window.draw(background2);
        // cout << "Mangekyou scale  x : " << mangekyou.getScale().x << " y :" << mangekyou.getScale().y << endl;

    }

    virtual ~level()
    {
        for (int i = 0; i < enemy_number; ++i)
        {
            delete eship_ptr[i];
        }
        delete[] eship_ptr;
    }
};

class lvl1 : public level
{
public:
    void Shapes() override;
    lvl1()
    {
        lvl_no = 1;
        enemy_number = 20;
        Background.loadFromFile("img/background_1.png");
        background1.setTexture(&Background);
        background2.setTexture(&Background);
        eship_ptr = new Invader *[enemy_number];
        lvl_txt.setString("Level : " + to_string(lvl_no));

        for (int counter = 0; counter < enemy_number; counter++)
        {
            randomizer = rand() % 3;
            if (randomizer == 0)
                eship_ptr[counter] = new alpha(50);
            else if (randomizer == 1)
                eship_ptr[counter] = new beta(50);
            else if (randomizer == 2)
                eship_ptr[counter] = new gamma(50);
        }
        Shapes();
    }
};

class lvl2 : public level
{
public:
    void Shapes() override;
    lvl2()
    {
        lvl_no = 2;
        enemy_number = 20;
        Background.loadFromFile("img/background_1.png");
        background1.setTexture(&Background);
        background2.setTexture(&Background);
        eship_ptr = new Invader *[enemy_number];
        lvl_txt.setString("Level : " + to_string(lvl_no));
        for (int counter = 0; counter < enemy_number; counter++)
        {
            randomizer = rand() % 3;
            if (randomizer == 0)
                eship_ptr[counter] = new alpha(75);
            else if (randomizer == 1)
                eship_ptr[counter] = new beta(75);
            else if (randomizer == 2)
                eship_ptr[counter] = new gamma(75);
        }
        Shapes();
    }
};

class lvl3 : public level
{
public:
    void Shapes() override;
    lvl3()  
    {  
        lvl_no = 3;
        enemy_number = 40;
        Background.loadFromFile("img/background_1.png");
        background1.setTexture(&Background);
        background2.setTexture(&Background);
        eship_ptr = new Invader *[enemy_number];
        lvl_txt.setString("Level : " + to_string(lvl_no));
        for (int counter = 0; counter < enemy_number; counter++)
        {
            randomizer = rand() % 3;
            if (randomizer == 0)
                eship_ptr[counter] = new alpha(100);
            else if (randomizer == 1)
                eship_ptr[counter] = new beta(100);
            else if (randomizer == 2)
                eship_ptr[counter] = new gamma(100);
        }
        Shapes();
    }
};

class monster_lvl : level
{
    public:
        monster_lvl()
        {
            lvl_no = 4;
            enemy_number = 0;
            Background.loadFromFile("img/background_1.png");
            background1.setTexture(&Background);
            background2.setTexture(&Background);
            lvl_txt.setString("Level : Monster");
        }
    
};

sf::Clock level::dragon_clock;
bool level::mangekyou_status = false;






