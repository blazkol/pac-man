#include <iostream>
#include "Pacman.h"


Pacman::Pacman() : Creature(){
    texture1.loadFromFile("assets/pacman1.png");
    texture2.loadFromFile("assets/pacman2.png");
    sprite.setTexture(texture1);
    sprite.setOrigin(16, 16);
    originX = 336;
    originY = 624;
}
Pacman::~Pacman(){}

void Pacman::setRotation(int x){
    sprite.setRotation(x);
}

void Pacman::setDirection(Direction direction){
    chosenDir = direction;
    currentDir = direction;
}

void Pacman::chooseDirection(Direction direction){
    if(direction == Left){chosenDir = Left;}
    else if(direction == Right){chosenDir = Right;}
    else if(direction == Up){chosenDir = Up;}
    else if(direction == Down){chosenDir = Down;}
}

void Pacman::movement(std::vector<GameObject> &walls){
    int x, y;
    unsigned int i;
    bool collision = 0;
    if(chosenDir == Left){x = -4; y = 0;}
    else if(chosenDir == Right){x = 4; y = 0;}
    else if(chosenDir == Up){x = 0; y = -4;}
    else if(chosenDir == Down){x = 0; y = 4;}
    else{x = 0; y = 0;}
    sprite.move(x, y);
    for(i = 0; i < walls.size(); i++){
        if(sprite.getGlobalBounds().intersects(walls[i].getBounds())){collision = 1;}
    }
    sprite.move(-x, -y);
    if(collision == 0){currentDir = chosenDir;}
    if(currentDir == Left){
        x = -4;
        y = 0;
        sprite.setRotation(180);
    } else if(currentDir == Right){
        x = 4;
        y = 0;
        sprite.setRotation(0);
    } else if(currentDir == Up){
        x = 0;
        y = -4;
        sprite.setRotation(-90);
    } else if(currentDir == Down){
        x = 0;
        y = 4;
        sprite.setRotation(90);
    } else{x = 0; y = 0;}
    sprite.move(x, y);
    for(i = 0; i < walls.size(); i++){
        if(sprite.getGlobalBounds().intersects(walls[i].getBounds())){sprite.move(-x, -y);}
    }
    teleport();
}
