#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>

class GameObject // base class for the Coin and BigCoin classes (by default it is wall)
{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    GameObject();
    ~GameObject();

    sf::Sprite getSprite();
    sf::FloatRect getBounds(); // method that returns boundary of the object
    void setPosition(int x, int y);
};

#endif // GAMEOBJECT_H_INCLUDED
