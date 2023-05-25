#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Score.h"
#include "GameObject.h"
#include "Coin.h"
#include "BigCoin.h"
#include "Pacman.h"
#include "Ghost.h"

class Game  // class that stores window, menu and objects of other classes
{
private:
    sf::RenderWindow window; // main window
    sf::Clock animClock, huntClock; // clocks used for "animateSprites" and "startHunting" methods
    sf::Texture menuTex; // texture for the menu
    sf::Sprite menuSpr; // sprite for the menu
    GameState gamestate; // enumeration included in Score.h, it indicates the state of the game
    Score score;
    GameObject wall;
    Coin coin;
    BigCoin bigcoin;
    Pacman pacman;
    Ghost blinky, pinky, inky, clyde;
    std::vector<GameObject> walls;
    std::vector<Coin> coins;
    std::vector<BigCoin> bigcoins;
    bool huntStart; // variable that indicates whether the "Hunting" state started or not

    void checkCollectibles(); // method that checks whether the Pac-Man collided with a Coin or BigCoin object
    void startHunting(); // method that turns the game state to "Hunting" when the Pac-Man can eat ghosts
    void updateGame(); // method that includes most of the actions performed by other stored objects
    void animateSprites(); // method for animating sprites
    void drawSprites(); // method for drawing all sprites beside sprite menu
    void loadMap(); // method for loading default position of objects stored in vectors: walls, coins and bigcoins from txt file
    void newGame();
    void saveGame();
    void loadGhost(std::ifstream &file, Ghost &ghost); // method that load data of one particular ghost, it is used in loadGame method
    void loadGame();
public:
    Game();
    ~Game();

    void run(); // method responsible for operations of the entire game
};

#endif // GAME_H_INCLUDED
