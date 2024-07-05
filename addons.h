#include <SFML/Graphics.hpp>

class addons
{
protected:
    sf::Sprite add;
    sf::Texture add_txt;
    Clock addclock;

    void run()
    {
    }

    virtual void effect() =0;
};

class life_up : addons
{
    life_up()
    {
        add_txt.loadFromFile("img/PNG/Power-ups/pill_red.png");
        add.setTexture(add_txt);
    }
};

class shield : addons
{
    shield()
    {
        add_txt.loadFromFile("img/PNG/Power-ups/shield_gold.png");
        add.setTexture(add_txt);
    }
};

class powerup : addons
{
    powerup() 
    {
    }
};

class fire : addons
{
    fire()
    {
    }
};
