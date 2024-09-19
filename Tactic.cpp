#include "Tactic.h"

#include <array>
#include <iostream>
#include <ostream>

Tactic::Tactic() {
    defenders = rand() % 8 + 1;
    middlers = rand() % (9 - defenders) + 1;
    strikers = 10 - middlers - defenders;
}

Tactic::Tactic(Tactic &tactic) {
    defenders = tactic.defenders;
    middlers = tactic.middlers;
    strikers = tactic.strikers;
}

Tactic::~Tactic() {

}

Tactic &Tactic::operator=(Tactic const &tactic) {
    this->defenders = tactic.defenders;
    this->middlers = tactic.middlers;
    this->strikers = tactic.strikers;
    return *this;
}

void Tactic::changeTactic(int d, int m) {
    if (d < 1 || m < 1 || d + m > 9) {
        std::cout << "Impossible tactic" << std::endl;
        return;
    }

    defenders = d;
    middlers = m;
    strikers = 10 - d - m;
}

std::string Tactic::getTactic() const {
    return std::to_string(this->defenders) + " " + std::to_string(this->middlers) + " " + std::to_string(this->strikers);
}

std::ostream &operator<<(std::ostream &os, Tactic const &tactic) {
    os << tactic.getTactic();
    return os;
}

std::array<int, 4> Tactic::getTacticInt() {
    std::array<int, 4> arr;
    arr[0] = 1;
    arr[1] = defenders;
    arr[2] = middlers;
    arr[3] = strikers;
    return arr;
}

std::istream &operator>>(std::istream &is, Tactic &tactic) {
    is >> tactic.defenders >> tactic.middlers >> tactic.strikers;
    return is;
}