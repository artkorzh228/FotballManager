#ifndef MIDFIELDER_H
#define MIDFIELDER_H
#include "Player.h"


class Midfielder: public Player {
protected:
    //Midfielder
    int shortPass;
    int longPass;
public:
    int position;
    Midfielder();
    ~Midfielder() = default;
    void train() override;
    void print() override;
    int getPower() override;
    int getPosition() override;
    void save(std::ostream &os) override;
    void load(std::istream &is) override;
};



#endif //MIDFIELDER_H
