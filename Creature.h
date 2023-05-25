#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GameObject.h"

enum Direction{None, Left, Right, Up, Down}; // enumeration that indicates direction of moving object

class Creature // abstract base class for the Pacman and Ghost classes
{
protected:
    sf::Texture texture1, texture2;
    sf::Sprite sprite;
    Direction currentDir; // the current direction of movement of the object
    int originX, originY; // variables indicating original position of the object
    bool texChange; // variable used in animation method
public:
    Creature();
    virtual ~Creature() = 0;

    Direction getCurrentDir();
    sf::Sprite getSprite();
    sf::FloatRect getBounds(); // method that returns boundary of the object
    sf::Vector2f getPosition();
    virtual void setDirection(Direction direction); // method that sets currentDir variable
    void setPosition(); // method that sets position of object to original one
    void setPosition(int x, int y); // method that sets position of object to selected one
    void teleport(); // method that changes position of object when it is located on the right or left border of the map
    void animation(sf::Clock &animClock);
};

#endif // CREATURE_H_INCLUDED
