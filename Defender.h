#ifndef DEFENDER_H
#define DEFENDER_H
#include "Player.h"


class Defender: public Player {
protected:
    //defense
    int tackle;
    int interception;
public:
    int position;
    Defender();
    ~Defender() = default;
    void train() override;
    void save(std::ostream& os) override;
    void load(std::istream &is) override;
    void print() override;
    int getPower() override;
    int getPosition() override;
    friend std::ostream &operator<<(std::ostream &os, Defender const &player);
    friend std::istream &operator>>(std::istream &is, Defender &player);
};



#endif //DEFENDER_H
