#include <iostream>
#include <fstream>
#include "Game.h"

Game::Game() :
window(sf::VideoMode(672, 832), "Pac-Man"),
blinky(sf::Color::Red, 336, 400), pinky(sf::Color::Magenta, 336, 432), inky(sf::Color::Cyan, 368, 432), clyde(sf::Color::Yellow, 304, 432)
{
    window.setFramerateLimit(30);
    menuTex.loadFromFile("assets/menu.png");
    menuSpr.setTexture(menuTex);
    gamestate = MENU;
    huntStart = 0;
    loadMap();
}
Game::~Game(){}

void Game::checkCollectibles(){
    unsigned int i;
    bool flag1 = 0;
    bool flag2 = 0;
    for(i = 0; i < coins.size(); i++){
        coins[i].collect(pacman, score);
        if(coins[i].getState() == 1){flag1 = 1;}
    }
    for(i = 0; i < bigcoins.size(); i++){
        bigcoins[i].collect(pacman, score, gamestate, huntStart);
        if(bigcoins[i].getState() == 1){flag2 = 1;}
    }
    if(flag1 == 0 && flag2 == 0){
        gamestate = Victory;
        score.setStateText(gamestate);
    }
}

void Game::startHunting(){
    if(gamestate == Hunting && huntStart == 0){
        huntClock.restart();
        huntStart = 1;
    }
    if(huntStart == 1 && huntClock.getElapsedTime().asSeconds() >= 8.0f){
        gamestate = Normal;
        huntStart = 0;
    }
}

void Game::updateGame(){
    if(gamestate == Normal || gamestate ==  Hunting){
        pacman.movement(walls);
        blinky.movement(walls);
        pinky.movement(walls);
        inky.movement(walls);
        clyde.movement(walls);
        blinky.actions(pacman, score, gamestate, huntStart);
        pinky.actions(pacman, score, gamestate, huntStart);
        inky.actions(pacman, score, gamestate, huntStart);
        clyde.actions(pacman, score, gamestate, huntStart);
        checkCollectibles();
        startHunting();
    }
}

void Game::animateSprites(){
    pacman.animation(animClock);
    blinky.animation(animClock);
    pinky.animation(animClock);
    inky.animation(animClock);
    clyde.animation(animClock);
    if(animClock.getElapsedTime().asSeconds() > 0.25f){
        animClock.restart();
    }
}

void Game::drawSprites(){
    unsigned int i;
    for(i = 0; i < walls.size(); i++){
        window.draw(walls[i].getSprite());
    }
    for(i = 0; i < coins.size(); i++){
        if(coins[i].getState() == 1){
            window.draw(coins[i].getSprite());
        }
    }
    for(i = 0; i < bigcoins.size(); i++){
        if(bigcoins[i].getState() == 1){
            window.draw(bigcoins[i].getSprite());
        }
    }
    window.draw(score.getPointsText());
    window.draw(score.getLivesText());
    window.draw(pacman.getSprite());
    window.draw(blinky.getSprite());
    window.draw(pinky.getSprite());
    window.draw(inky.getSprite());
    window.draw(clyde.getSprite());
    window.draw(score.getPointsText());
    window.draw(score.getLivesText());
    window.draw(score.getStateText());
}

void Game::loadMap(){
    char load;
    std::ifstream FILE;
    FILE.open("map.txt");
    if(FILE.is_open()){
        for(int r = 0; r < 26; r++){
            for(int c = 0; c < 21; c++){
                FILE >> load;
                if(load == '1'){
                    walls.push_back(wall);
                    walls[walls.size() - 1].setPosition(c*32, r*32);
                } else if(load == '2'){
                    coins.push_back(coin);
                    coins[coins.size() - 1].setPosition(c*32, r*32);
                } else if(load == '3'){
                    bigcoins.push_back(bigcoin);
                    bigcoins[bigcoins.size() - 1].setPosition(c*32, r*32);
                }
            }
        }
    } else{
        std::cout << "Error: map.txt not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    FILE.close();
}

void Game::newGame(){
    gamestate = Normal;
    pacman.setPosition();
    pacman.setDirection(None);
    pacman.setRotation(0);
    blinky.setPosition();
    pinky.setPosition();
    inky.setPosition();
    clyde.setPosition();
    unsigned int i;
    for(i = 0; i < coins.size(); i++){
        coins[i].setState(1);
    }
    for(i = 0; i < bigcoins.size(); i++){
        bigcoins[i].setState(1);
    }
    score.setPoints(0);
    score.setLives(3);
    score.setStateText(gamestate);
}

void Game::saveGame(){
    std::ofstream FILE;
    unsigned int i;
    FILE.open("Save.txt");
    for(i = 0; i < coins.size(); i++){
        FILE << coins[i].getState();
    }
    FILE << "\n";
    for(i = 0; i < bigcoins.size(); i++){
        FILE << bigcoins[i].getState();
    }
    FILE << "\n" << gamestate << "\n";
    FILE << score.getPoints() << "\n";
    FILE << score.getLives() << "\n";
    FILE << pacman.getPosition().x << "\n";
    FILE << pacman.getPosition().y << "\n";
    FILE << pacman.getCurrentDir() << "\n";
    FILE << blinky.getPosition().x << "\n";
    FILE << blinky.getPosition().y << "\n";
    FILE << blinky.getCurrentDir() << "\n";
    FILE << blinky.getState() << "\n";
    FILE << pinky.getPosition().x << "\n";
    FILE << pinky.getPosition().y << "\n";
    FILE << pinky.getCurrentDir() << "\n";
    FILE << pinky.getState() << "\n";
    FILE << inky.getPosition().x << "\n";
    FILE << inky.getPosition().y << "\n";
    FILE << inky.getCurrentDir() << "\n";
    FILE << inky.getState() << "\n";
    FILE << clyde.getPosition().x << "\n";
    FILE << clyde.getPosition().y << "\n";
    FILE << clyde.getCurrentDir() << "\n";
    FILE << clyde.getState() << "\n";
    FILE.close();
}

void Game::loadGhost(std::ifstream &file, Ghost &ghost){
    char load;
    int x, y;
    file >> x;
    file >> y;
    ghost.setPosition(x, y);
    file >> load;
    if(load == '0'){ghost.setDirection(None);}
    else if(load == '1'){ghost.setDirection(Left);}
    else if(load == '2'){ghost.setDirection(Right);}
    else if(load == '3'){ghost.setDirection(Up);}
    else if(load == '4'){ghost.setDirection(Down);}
    file >> load;
    if(load == '0'){ghost.setState(0);}
    else if(load == '1'){ghost.setState(1);}
}

void Game::loadGame(){
    std::ifstream FILE;
    char load;
    int points, lives, x, y;
    unsigned int i;
    FILE.open("Save.txt");
    if(FILE.is_open()){
        for(i = 0; i < coins.size(); i++){
            FILE >> load;
            if(load == '0'){coins[i].setState(0);}
            else if(load == '1'){coins[i].setState(1);}
        }
        for(i = 0; i < bigcoins.size(); i++){
            FILE >> load;
            if(load == '0'){bigcoins[i].setState(0);}
            else if(load == '1'){bigcoins[i].setState(1);}
        }
        FILE >> load;
        if(load == '0'){gamestate = Normal;}
        else if(load == '1'){
            gamestate = Hunting;
            huntStart = 0;
            startHunting();
        }
        else if(load == '2'){gamestate = Defeat;}
        else if(load == '3'){gamestate = Victory;}
        score.setStateText(gamestate);
        FILE >> points;
        score.setPoints(points);
        FILE >> lives;
        score.setLives(lives);
        FILE >> x;
        FILE >> y;
        pacman.setPosition(x, y);
        FILE >> load;
        if(load == '0'){pacman.setDirection(None);}
        else if(load == '1'){pacman.setDirection(Left);}
        else if(load == '2'){pacman.setDirection(Right);}
        else if(load == '3'){pacman.setDirection(Up);}
        else if(load == '4'){pacman.setDirection(Down);}
        loadGhost(FILE, blinky);
        loadGhost(FILE, pinky);
        loadGhost(FILE, inky);
        loadGhost(FILE, clyde);
    } else{
        std::cout << "Error: save.txt not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    FILE.close();
}

void Game::run(){
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                exit(EXIT_SUCCESS);
            }
            else if(event.type == sf::Event::MouseButtonPressed && gamestate == MENU){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(event.mouseButton.x > 240 && event.mouseButton.x < 440){
                        if(event.mouseButton.y > 190 && event.mouseButton.y < 260){newGame();}
                        else if(event.mouseButton.y > 280 && event.mouseButton.y < 350){loadGame();}
                        else if(event.mouseButton.y > 370 && event.mouseButton.y < 440){exit(EXIT_SUCCESS);}
                    }
                }
            }
            else if(event.type == sf::Event::KeyPressed && gamestate != MENU){
                if(event.key.code == sf::Keyboard::S){saveGame();}
                else if(event.key.code == sf::Keyboard::L){loadGame();}
                else if(event.key.code == sf::Keyboard::Left){pacman.chooseDirection(Left);}
                else if(event.key.code == sf::Keyboard::Right){pacman.chooseDirection(Right);}
                else if(event.key.code == sf::Keyboard::Up){pacman.chooseDirection(Up);}
                else if(event.key.code == sf::Keyboard::Down){pacman.chooseDirection(Down);}
                else if(event.key.code == sf::Keyboard::Escape){gamestate = MENU;}
            }
        }
        updateGame();
        window.clear();
        if(gamestate == MENU){window.draw(menuSpr);}
        else{
            animateSprites();
            drawSprites();
        }
        window.display();
    }
}
