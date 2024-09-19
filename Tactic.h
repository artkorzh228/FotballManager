#ifndef TACTIC_H
#define TACTIC_H

#include <array>
#include "Player.h"


class Tactic {
protected:
    int defenders;
    int middlers;
    int strikers;
public:
    Tactic();
    Tactic(Tactic &tactic);
    ~Tactic();
    std::string getTactic() const;
    std::array<int, 4> getTacticInt();
    Tactic& operator= (const Tactic &tactic);
    friend std::ostream &operator<<(std::ostream &os, Tactic const &tactic);
    friend std::istream &operator>>(std::istream &is, Tactic &tactic);
    void changeTactic(int, int);
};



#endif //TACTIC_H
