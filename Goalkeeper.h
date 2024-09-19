#ifndef GOALKEEPER_H
#define GOALKEEPER_H
#include "Player.h"


class Goalkeeper: public Player {
protected:
    //additional
    int goalkeeping;
    int reaction;
public:
    int position;
    Goalkeeper();
    ~Goalkeeper() = default;
    void train() override;
    void print() override;
    int getPower() override;
    int getPosition() override;
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
};



#endif //GOALKEEPER_H
