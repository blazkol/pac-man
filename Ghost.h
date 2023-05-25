#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "Creature.h"
#include "Collectible.h"
#include "Pacman.h"
#include "Score.h"

class Ghost : public Creature, public Collectible // class for main enemies of Pac-Man
{
private:
    sf::Color originalColor;
    Direction oppositeDir; // variable that indicates direction opposite to current one
    bool attitude; // variable that indicates whether ghost is in normal mode or frightened (can be eaten by Pac-Man)

    void randDirection(); // method that sets currentDir variable to random one
    void checkHome(); // method that sets direction of the ghost so that it can leave the ghost's house in the center of the map
    void checkCrossroads(); // method that checks whether ghost is located at the crossroad and calls randDirection method
    void checkGameState(GameState &gamestate, bool &huntStart); // method that checks whether game state is set to "Hunting" and changes attitude of the ghost
    void kill(Pacman &pacman, Score &score, GameState &state); // method called whether ghost collided with Pac-Man while the ghost attitude is set to 0
    void die(Pacman &pacman, Score &score); // method called whether ghost collided with Pac-Man while the ghost attitude is set to 1
public:
    Ghost(sf::Color color, int x, int y);
    ~Ghost();

    void movement(std::vector<GameObject> &walls);
    void actions(Pacman &pacman, Score &score, GameState &state, bool &huntStart); // method which includes other methods from the ghost class and its later called in the game class
};

#endif // GHOST_H_INCLUDED
