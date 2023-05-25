#include "Collectible.h"

Collectible::Collectible(){
    state = 1;
}
Collectible::~Collectible(){}

int Collectible::getValue(){
    return value;
}

bool Collectible::getState(){
    return state;
}

void Collectible::setState(bool x){
    state = x;
}

