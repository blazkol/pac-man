#include "BigCoin.h"

BigCoin::BigCoin() : Collectible(){
    texture.loadFromFile("assets/bigcoin.png");
    sprite.setTexture(texture);
    value = 50;
}
BigCoin::~BigCoin(){}

void BigCoin::collect(Pacman &pacman, Score &score, GameState &gamestate, bool &huntStart){
    if(state == 1 && sprite.getGlobalBounds().intersects(pacman.getBounds())){
        state = 0;
        score.setPoints(score.getPoints() + value);
        gamestate = Hunting;
        huntStart = 0;
    }
}
