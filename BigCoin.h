#ifndef BIGCOIN_H_INCLUDED
#define BIGCOIN_H_INCLUDED

#include "Collectible.h"
#include "Pacman.h"
#include "Score.h"

class BigCoin : public Collectible, public GameObject // class for large, collectible in-game objects that give the player ability to eat ghosts
{
public:
    BigCoin();
    ~BigCoin();

    void collect(Pacman &pacman, Score &score, GameState &state, bool &huntStart); // similar to collect method in Coin class but it also sets the game state to "Hunting"
};

#endif // BIGCOIN_H_INCLUDED
