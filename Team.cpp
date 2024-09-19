#include "Team.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <ostream>
#include <string>

#include "Defender.h"
#include "Forward.h"
#include "Goalkeeper.h"
#include "Midfielder.h"

Team::Team() {
    tactic = nullptr;
    start = {nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr,nullptr};
}

Team::Team(const int number, const std::string& n) {
    name = number == 0 ? n : "Team " + std::to_string(number);
    tactic = new Tactic();

    std::array<int, 4> tacticArr;
    if (number == 0) {
        tacticArr[0] = 3;
        tacticArr[1] = 4;
        tacticArr[2] = 4;
        tacticArr[3] = 4;
    } else {
        tacticArr = tactic->getTacticInt();
    }


    for (int i = 0; i < 4; i++) {
        const int q = tacticArr[i];
        for (int j = 0; j < q; j++) {
            switch (i) {
                case 0:
                    squad.push_back(new Goalkeeper());
                break;
                case 1:
                    squad.push_back(new Defender());
                break;
                case 2:
                    squad.push_back(new Midfielder());
                break;
                case 3:
                    squad.push_back(new Forward());
                break;
                default:
                    break;
            }
        }
    }

    if (number == 0) {
        budget = 10;
        start = {nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr,nullptr};
    } else {
        budget = 0;
        for (int i = 0; i < 11; i++) {
            start[i] = squad[i];
        }
    }
}

Team::~Team() {
    delete tactic;
    for (const Player* player : squad) {
        delete player;
    }
}

void Team::printSquad() const {
    std::cout << name << " squad is:" << std::endl;
    for (int i = 0; i < squad.size(); i++) {
        std::cout << i << ". ";
        squad[i]->print();
        std::cout << std::endl;
    }
}

void Team::printTactic() {
    std::cout << name << " tactic is " << *tactic << std::endl;
}

void Team::printStart() {
    for (int i = 0; i < 11; i++) {
        std::cout << i << ". ";
        if (start[i] != nullptr) {
            start[i]->print();
        }
        std::cout << std::endl;
    }
}

void Team::setStart() {
    std::array<int, 4> tacticArr = tactic->getTacticInt();
    std::array<std::string, 4> positions = {"Goalkeeper", "Defender", "Midfielder", "Forward"};

    int counter = 0;
    for (int i = 0; i < 4; i++) {
        const int q = tacticArr[i];
        for (int j = 0; j < q; j++) {
            int select = -1;
            std::vector<Player *> x = freePlayers(i, counter);
            if (x.size() == 0) {
                std::cout << "Impossible to set first 11. Try to change tactic." << std::endl;
                return;
            }
            while (select < 0 || select >= x.size()) {
                std::cout << "Select Player on position " << positions[i] << std::endl;
                for (int k = 0; k < x.size(); k++) {
                    std::cout << k << " : ";
                    x[k]->print();
                    std::cout << std::endl;
                }
                std::cin >> select;
                if (select < 0 || select >= x.size()) {
                    std::cout << "Wrong input" << std::endl;
                }
            }
            start[counter++] = x[select];
        }
    }
}

std::vector<Player *> Team::freePlayers(int pos, int counter) {
    std::vector<Player*> x;
    std::copy_if(squad.begin(), squad.end(), std::back_inserter(x), [pos, counter, this](Player* p) {
        for (int c = 0; c < counter; c++) {
            if (!!start[c] && start[c]->id == p->id) {
                return false;
            }
        }
        return p->getPosition() == pos && p->stamina != 0;
    });
    return x;
}

void Team::swapPlayer(int a) {
    std::array<std::string, 4> positions = {"Goalkeeper", "Defender", "Midfielder", "Forward"};
    int pos = start[a]->getPosition();
    start[a] = nullptr;
    std::vector<Player *> x = freePlayers(pos);
    if (x.size() == 0) {
        std::cout << "No players for this position, try to change tactic" << std::endl;
        return;
    }
    int select = -1;
    while (select < 0 || select >= x.size()) {
        std::cout << "Select Player on position " << positions[pos] << std::endl;
        for (int k = 0; k < x.size(); k++) {
            std::cout << k << " : ";
            x[k]->print();
            std::cout << std::endl;
        }
        std::cin >> select;
        if (select < 0 || select >= x.size()) {
            std::cout << "Wrong input" << std::endl;
        }
    }
    start[a] = x[select];
}

std::istream &operator>>(std::istream &is, Team &team) {
    std::getline(is, team.name);
    is >> team.budget;
    team.tactic = new Tactic();
    is >> *(team.tactic);
    int squadSize;
    is >> squadSize;
    team.squad.clear();
    int position;
    bool isSelected;
    std::string emptyline;
    int counter = 0;
    for (int i = 0; i < squadSize; i++) {
        is >> position >> isSelected;
        std::getline(is, emptyline);
        Player* player = nullptr;
        switch (position) {
            case 0: {
                auto *gk = new Goalkeeper();
                gk->load(is);
                player = gk;
                break;
            }
            case 1: {
                auto *df = new Defender();
                df->load(is);
                player = df;
                break;
            }
            case 2: {
                auto *mf = new Midfielder();
                mf->load(is);
                player = mf;
                break;
            }
            case 3: {
                auto *fr = new Forward();
                fr->load(is);
                player = fr;
                break;
            }
            default: {
                std::cout << "Wrong input" << std::endl;
                break;
            }
        }

        if (player == nullptr) {
            return is;
        }

        team.squad.push_back(player);
        if (isSelected) {
            team.start[counter++] = player;
        }

    }
    int journalSize;
    is >> journalSize;
    std::getline(is, emptyline);
    for (int i = 0; i < journalSize; i++) {
        std::string line;
        std::getline(is, line);
        team.history.push_back(line);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Team &team) {
    os << team.name << std::endl;
    os << team.budget << std::endl;
    os << *(team.tactic) << std::endl;
    os << team.squad.size() << std::endl;
    for (int i = 0; i < team.squad.size(); i++) {
        os << team.squad[i]->getPosition() << std::endl;
        bool isSelected = false;
        for (int j = 0; j < 11; j++) {
            if (team.start[j] == team.squad[i]) {
                isSelected = true;
                break;
            }
        }
        os << isSelected << std::endl;
        team.squad[i]->save(os);
    }
    os << team.history.size() << std::endl;
    for (const auto & it : team.history) {
        os << it << std::endl;
    }
    return os;
}

std::array<int, 4> Team::getPower() {
    std::array<int, 4> arr = { 0, 0, 0, 0};
    for (int i = 0; i < 11; i++) {
        if (start[i] == nullptr) {
            continue;
        }
        const int type = start[i]->getPosition();
        arr[type] += start[i]->getPower();
    }
    return arr;
}

void Team::printPower() {
    std::array<int, 4> arr = getPower();
    std::cout << "GKP: " << arr[0] << ", DEF: " << arr[1] << ", MDF: " << arr[2] << ", ATC: " << arr[3] << std::endl;
}

void Team::setTactic(const int d, const int m) {
    tactic->changeTactic(d, m);
}

bool Team::checkStart11() {
    for (int i = 0; i < 11; i++) {
        if (start[i] == nullptr || start[i]->stamina == 0) {
            return false;
        }
    }
    return true;
}
