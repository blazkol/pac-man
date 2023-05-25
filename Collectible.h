#ifndef COLLECTIBLE_H_INCLUDED
#define COLLECTIBLE_H_INCLUDED

class Collectible // abstract base class for the Coin, BigCoin and Ghost classes
{
protected:
    int value; // value added to the game score after collecting object
    bool state; // variable which indicate whether object was collected or not by Pac-Man
public:
    Collectible();
    virtual ~Collectible() = 0;

    int getValue();
    bool getState();
    void setState(bool x);
};

#endif // COLLECTIBLE_H_INCLUDED
