#include "Creature.h"

Creature::Creature(){
    currentDir = None;
    texChange = 0;
}
Creature::~Creature(){}

Direction Creature::getCurrentDir(){
    return currentDir;
}

sf::Sprite Creature::getSprite(){
    return sprite;
}

sf::FloatRect Creature::getBounds(){
    return sprite.getGlobalBounds();
}

sf::Vector2f Creature::getPosition(){
    return sprite.getPosition();
}

void Creature::setDirection(Direction direction){
    currentDir = direction;
}

void Creature::setPosition(){
    sprite.setPosition(originX, originY);
}

void Creature::setPosition(int x, int y){
    sprite.setPosition(x, y);
}

void Creature::teleport(){
    sf::Vector2f position = sprite.getPosition();
    if(position.x == 0 && position.y == 432){sprite.setPosition(672, 432);}
    else if(position.x == 672 && position.y == 432){sprite.setPosition(0, 432);}
}

void Creature::animation(sf::Clock &animClock){
    if(animClock.getElapsedTime().asSeconds() > 0.25f && texChange == 0){
        sprite.setTexture(texture1);
        texChange = 1;
    } else if(animClock.getElapsedTime().asSeconds() > 0.25f && texChange == 1){
        sprite.setTexture(texture2);
        texChange = 0;
    }
}

