#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "Collectible.h"
#include "Pacman.h"
#include "Score.h"

class Coin : public Collectible, public GameObject // class for small, collectible in-game objects
{
public:
    Coin();
    ~Coin();

    void collect(Pacman &pacman, Score &score); // method that checks if Pac-Man collided with the Coin object and adds its value to the game score
};

#endif // COIN_H_INCLUDED
