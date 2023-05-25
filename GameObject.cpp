#include "GameObject.h"

GameObject::GameObject(){
    texture.loadFromFile("assets/wall.png");
    sprite.setTexture(texture);
}
GameObject::~GameObject(){}

sf::Sprite GameObject::getSprite(){
    return sprite;
}

sf::FloatRect GameObject::getBounds(){
    return sprite.getGlobalBounds();
}

void GameObject::setPosition(int x, int y){
    sprite.setPosition(x, y);
}
