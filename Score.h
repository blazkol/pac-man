#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>

enum GameState{Normal, Hunting, Defeat, Victory, MENU}; // enumeration that indicates state of game

class Score // class which stores and displays information about current points and lives. It also has a method which indicates whether the game is won or lost
{
private:
    sf::Font font;
    sf::Text pointsText, livesText, stateText; // texts displayed on the screen
    int points, lives;
public:
    Score();
    ~Score();

    sf::Text getPointsText();
    sf::Text getLivesText();
    sf::Text getStateText();
    int getPoints();
    int getLives();
    void setPoints(int x);
    void setLives(int x);
    void setStateText(GameState &gamestate);
};

#endif // SCORE_H_INCLUDED
