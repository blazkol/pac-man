#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "Creature.h"

class Pacman : public Creature // class for the object controlled by the player (Pac-Man)
{
private:
    Direction chosenDir; // direction set by the player by pressing the appropriate key
public:
    Pacman();
    ~Pacman();

    void setRotation(int x);
    void setDirection(Direction direction);
    void chooseDirection(Direction direction);
    void movement(std::vector<GameObject> &walls);
};

#endif // PACMAN_H_INCLUDED
