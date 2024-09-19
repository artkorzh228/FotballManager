#ifndef TEAM_H
#define TEAM_H
#include <array>
#include <list>
#include <vector>

#include "Player.h"
#include "Tactic.h"


class Team {
public:
    std::vector<Player*> squad;
    std::list<std::string> history;
    Tactic *tactic;
    int budget;
    std::array<Player*, 11> start;
    std::string name;
    Team();
    explicit Team(int number, const std::string& name);
    ~Team();
    void printSquad() const;
    void printTactic();
    void printStart();
    void setStart();
    std::array<int, 4> getPower();
    void printPower();
    void setTactic(int, int);
    void swapPlayer(int a);
    bool checkStart11();
    std::vector<Player*> freePlayers(int pos, int counter = 10);
    friend std::istream &operator>>(std::istream &is, Team &team);
    friend std::ostream &operator<<(std::ostream &os, const Team &team);
    friend class Player;
};



#endif //TEAM_H
