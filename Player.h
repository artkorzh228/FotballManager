#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "enums.h"


class Player {
protected:
    static int counter;
    std::string name;
    int id;
    int maxStamina;
    int strength;
    int speed;
public:
    int stamina;
    Player();
    void exhaust();
    void rest();
    friend class Team;
    friend int main();
    virtual int getPosition() = 0;
    virtual void train() = 0;
    virtual void print() = 0;
    virtual void save(std::ostream& os) = 0;
    virtual void load(std::istream& is) = 0;
    virtual int getPower() = 0;
};



#endif //PLAYER_H
