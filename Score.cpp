#include <iostream>
#include <sstream>
#include "Score.h"

Score::Score(){
    font.loadFromFile("assets/font.ttf");
    pointsText.setFont(font);
    livesText.setFont(font);
    stateText.setFont(font);
    pointsText.setCharacterSize(28);
    livesText.setCharacterSize(28);
    stateText.setCharacterSize(28);
    pointsText.setFillColor(sf::Color::Yellow);
    livesText.setFillColor(sf::Color::Yellow);
    stateText.setFillColor(sf::Color::Yellow);
    pointsText.setPosition(16, 20);
    livesText.setPosition(256, 20);
    stateText.setPosition(480, 20);
}
Score::~Score(){}

sf::Text Score::getPointsText(){
    return pointsText;
}

sf::Text Score::getLivesText(){
    return livesText;
}

sf::Text Score::getStateText(){
    return stateText;
}

int Score::getPoints(){
    return points;
}

int Score::getLives(){
    return lives;
}

void Score::setPoints(int x){
    points = x;
    std::string pString;
    std::stringstream pStream;
    pStream << "Score:" << points;
    pString = pStream.str();
    pointsText.setString(pString);
}

void Score::setLives(int x){
    lives = x;
    std::string lString;
    std::stringstream lStream;
    lStream << "Lives:" << lives;
    lString = lStream.str();
    livesText.setString(lString);
}

void Score::setStateText(GameState &gamestate){
    if(gamestate == Defeat){stateText.setString("You lost!");}
    else if(gamestate == Victory){stateText.setString("You won!");}
    else{stateText.setString("");}
}
