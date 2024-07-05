#include <SFML/Graphics.hpp>

class Bullet
{
public:    
    sf::Sprite sprite;

    Bullet(const sf::Texture &texture, const sf::Vector2f &position)
    {
        sprite.setTexture(texture);
        sprite.setScale(1.0f, 1.0f);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(position);
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
    }  

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    sf::FloatRect getBounds() const
    {
        return sprite.getGlobalBounds();
    }
};
