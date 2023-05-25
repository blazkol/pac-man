#include <cstdlib>
#include <ctime>
#include "Ghost.h"

Ghost::Ghost(sf::Color color, int x, int y) : Creature(), Collectible(){
    texture1.loadFromFile("assets/ghost1.png");
    texture2.loadFromFile("assets/ghost2.png");
    originalColor = color;
    sprite.setTexture(texture1);
    sprite.setOrigin(16, 16);
    sprite.setColor(originalColor);
    originX = x;
    originY = y;
    value = 100;
}
Ghost::~Ghost(){}

void Ghost::randDirection(){
    int n = rand() % 4;
    if(n == 0){currentDir = Left;}
    else if(n == 1){currentDir = Right;}
    else if(n == 2){currentDir = Up;}
    else if(n == 3){currentDir = Down;}
}

void Ghost::checkHome(){
    sf::Vector2f position = sprite.getPosition();
    if(position.x == 336 && position.y == 400){currentDir = Up;}
    else if(position.x == 336 && position.y == 432){currentDir = Up;}
    else if(position.x == 368 && position.y == 432){currentDir = Left;}
    else if(position.x == 304 && position.y == 432){currentDir = Right;}
}

void Ghost::checkCrossroads(){
    sf::Vector2f c1(176,144), c2(496,144);
    sf::Vector2f c3(80,240), c4(176,240), c5(240,240), c6(304, 240), c7(368,240), c8(432,240), c9(496,240), c10(592,240);
    sf::Vector2f c11(176,304), c12(496, 304);
    sf::Vector2f c13(304,368), c14(368, 368);
    sf::Vector2f c15(176,432), c16(240,432), c17(432,432), c18(496,432);
    sf::Vector2f c19(240,496), c20(432,496);
    sf::Vector2f c21(176,560), c22(496,560);
    sf::Vector2f c23(176,624), c24(240,624), c25(304,624), c26(368,624), c27(432,624), c28(496,624);
    sf::Vector2f c29(112,688), c30(560,688);
    sf::Vector2f c31(304,752), c32(368,752);
    sf::Vector2f position = sprite.getPosition();
    if(position == c1 || position == c2 || position == c3 || position == c4 || position == c5 || position == c6 || position == c7 ||
       position == c8 || position == c9 || position == c10 || position == c11 || position == c12 || position == c13 || position == c14 ||
       position == c15 || position == c16 || position == c17 || position == c18 || position == c19 || position == c20 || position == c21 ||
       position == c22 || position == c23 || position == c24 || position == c25 || position == c26 || position == c27 || position == c28 ||
       position == c29 || position == c30 || position == c31 || position == c32){
        do{randDirection();} while(currentDir == oppositeDir);
    }
}

void Ghost::checkGameState(GameState &gamestate, bool &huntStart){
    if(gamestate == Hunting && state == 1){
        texture1.loadFromFile("assets/altghost1.png");
        texture2.loadFromFile("assets/altghost2.png");
        sprite.setColor(sf::Color::White);
        attitude = 1;
    } else if(gamestate == Normal || state == 0){
        texture1.loadFromFile("assets/ghost1.png");
        texture2.loadFromFile("assets/ghost2.png");
        sprite.setColor(originalColor);
        attitude = 0;
    } if(huntStart == 0){state = 1;}
}

void Ghost::kill(Pacman &pacman, Score &score, GameState &gamestate){
    if(attitude == 0 && score.getLives() > 0 && sprite.getGlobalBounds().intersects(pacman.getBounds())){
        pacman.setPosition();
        pacman.setDirection(None);
        score.setLives(score.getLives() - 1);
        if(score.getLives() == 0){
            gamestate = Defeat;
            score.setStateText(gamestate);
        }
    }
}

void Ghost::die(Pacman &pacman, Score &score){
    if(attitude == 1 && state == 1 && sprite.getGlobalBounds().intersects(pacman.getBounds())){
        state = 0;
        score.setPoints(score.getPoints() + value);
        setPosition();
    }
}

void Ghost::movement(std::vector<GameObject> &walls){
    bool collision = 0;
    int x, y;
    unsigned int i;
    checkHome();
    checkCrossroads();
    if(currentDir == Left){x = -4; y = 0;}
    else if(currentDir == Right){x = 4; y = 0;}
    else if(currentDir == Up){x = 0; y = -4;}
    else if(currentDir == Down){x = 0; y = 4;}
    else{x = 0; y = 0;}
    sprite.move(x, y);
    for(i = 0; i < walls.size(); i++){
        if(sprite.getGlobalBounds().intersects(walls[i].getBounds())){
            collision = 1;
            sprite.move(-x, -y);
            do{randDirection();} while(currentDir == oppositeDir);
        }
    }
    if(collision == 0 && currentDir == Left){oppositeDir = Right;}
    else if(collision == 0 && currentDir == Right){oppositeDir = Left;}
    else if(collision == 0 && currentDir == Up){oppositeDir = Down;}
    else if(collision == 0 && currentDir == Down){oppositeDir = Up;}
    teleport();
}

void Ghost::actions(Pacman &pacman, Score &score, GameState &gamestate, bool &huntStart){
    checkGameState(gamestate, huntStart);
    kill(pacman, score, gamestate);
    die(pacman, score);
}
