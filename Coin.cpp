#include "Coin.h"

Coin::Coin() : Collectible(){
    texture.loadFromFile("assets/coin.png");
    sprite.setTexture(texture);
    value = 10;
}
Coin::~Coin(){}

void Coin::collect(Pacman &pacman, Score &score){
    if(state == 1 && sprite.getGlobalBounds().intersects(pacman.getBounds())){
        state = 0;
        score.setPoints(score.getPoints() + value);
    }
}
