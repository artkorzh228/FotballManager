#ifndef FORWARD_H
#define FORWARD_H
#include "Player.h"


class Forward: public Player {
protected:
    //forward
    int shot;
    int dribbling;
public:
    int position;
    Forward();
    ~Forward() = default;
    void train() override;
    void print() override;
    int getPower() override;
    int getPosition() override;
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
};



#endif //FORWARD_H
