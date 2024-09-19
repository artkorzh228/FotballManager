#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "Team.h"

int startMenu() {
    std::cout << "Welcome in football manager!" << std::endl;

    int choice = 0;
    while (choice < 1 || choice > 2) {
        std::cout << "1 - Start new game" << std::endl;
        std::cout << "2 - Load game" << std::endl;
        std::cout << "3 - Game rules" << std::endl;
        std::cin >> choice;
        if (choice == 3) {
            std::cout << "You will be in charge of managing a team of 15 football players. You have the ability to adjust tactics, select your starting 11, and more. Each player will lose 1 stamina point for every match they participate in. If a player skips a match, they will fully recover their stamina. You will also have a budget that must remain positive throughout the game. You'll lose part of your budget if you lose or draw against weaker opponents. You can use your budget to train players or purchase new ones. If, at any point, you don't have enough players to field a team or your budget goes negative, the game ends. Good luck!" << std::endl;
        }
    }

    return choice;
}

GameState beforeMatch(Team *team1, Team *team2) {
    std::cout << "Next match is against " << team2->name << std::endl;
    std::cout << "Select action:" << std::endl;
    std::cout << "1 - Opponent info" << std::endl;
    std::cout << "2 - My Squad" << std::endl;
    std::cout << "3 - My budget" << std::endl;
    std::cout << "4 - My start11" << std::endl;
    std::cout << "5 - Save and Exit" << std::endl;
    std::cout << "6 - Change player name" << std::endl;
    int action = -1;
    std::cin >> action;
    if (action >= 1 && action <= 6) {
        return static_cast<GameState>(action);
    }
    std::cout << "Invalid action!" << std::endl;
    return BeforeMatch;
}

GameState myStart11(Team *team1) {
    std::cout << "My tactic:" << std::endl;
    team1->printTactic();
    std::cout << "My start 11:" << std::endl;
    team1->printStart();
    std::cout << "Current power:" << std::endl;
    team1->printPower();
    std::cout << "Select action:" << std::endl;
    std::cout << "1 - Set all start 11" << std::endl;
    std::cout << "2 - Change Tactic" << std::endl;
    std::cout << "3 - Change 1 player" << std::endl;
    std::cout << "4 - Proceed to the match" << std::endl;
    int action = -1;
    std::cin >> action;
    GameState result;
    switch (action) {
        case 1: {
            team1->setStart();
            result = MyStart11;
            break;
        }
        case 2: {
            team1->start = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            int d, m;
            std::cout << "Enter number of defenders" << std::endl;
            std::cin >> d;
            if (d < 1 || d > team1->freePlayers(1).size()) {
                std::cout << "Invalid number" << std::endl;
                result = MyStart11;
                break;
            }
            std::cout << "Enter number of midfielders" << std::endl;
            std::cin >> m;
            if (m < 1 || (d + m) > 9 || m > team1->freePlayers(2).size() || (10 - m - d) > team1->freePlayers(3).size()) {
                std::cout << "Invalid number" << std::endl;
                result = MyStart11;
                break;
            }
            team1->setTactic(m, d);
            team1->printTactic();
            team1->setStart();
            result = MyStart11;
            break;
        }
        case 3: {
            std::cout << "Select index of player to change:" << std::endl;
            int index = -1;
            std::cin >> index;
            if (index < 0 || index > 10) {
                std::cout << "Invalid index" << std::endl;
                result = MyStart11;
                break;
            }
            const int type = team1->start[index]->getPosition();
            team1->start[index] = nullptr;
            std::cout << "Select player for this position:" << std::endl;
            std::vector<Player *> players = team1->freePlayers(type);
            int x = 0;
            for (auto & player : players) {
                std::cout << x++ << ". ";
                player->print();
                std::cout << std::endl;
            }
            int ind = -1;
            std::cin >> ind;
            if (ind < 0 || ind > x) {
                std::cout << "Invalid index" << std::endl;
                result = MyStart11;
                break;
            }
            team1->start[index] = players[ind];
            result = MyStart11;
            break;
        }
        case 4: {
            if (team1->checkStart11()) {
                result = ProceedToTheMatch;
                break;
            }
            result = MyStart11;
            break;
        }
        default: {
            result = MyStart11;
            break;
        }
    }
    return result;
}

GameState trainingCentre(Team *team1, Team *team2) {
    std::cout << "Welcome to training centre! Here you can train your players for 1 budget point. Player will loose 1 stamina point, but they may gain 1 additional permanent skill point. Plus, for 5 points, you can buy any player from your last opponents." << std::endl;
    std::cout << "Select action:" << std::endl;
    std::cout << "1 - Opponent info" << std::endl;
    std::cout << "2 - My Squad" << std::endl;
    std::cout << "3 - My budget" << std::endl;
    std::cout << "4 - Training" << std::endl;
    std::cout << "5 - Transfer" << std::endl;
    std::cout << "6 - Proceed to the next week" << std::endl;
    int action = -1;
    std::cin >> action;
    GameState result;
    switch (action) {
        case 1: {
            team2->printSquad();
            result = TrainingCentre;
            break;
        }
        case 2: {
            team1->printSquad();
            result = TrainingCentre;
            break;
        }
        case 3: {
            std::cout << "Your budget is " << team1->budget << std::endl;
            result = TrainingCentre;
            break;
        }
        case 4: {
            std::cout << "Select index of the player you want to train:" << std::endl;
            int index = -1;
            std::cin >> index;
            if (index < 0 || index > team1->squad.size()) {
                std::cout << "Invalid index" << std::endl;
                result = TrainingCentre;
                break;
            }
            team1->budget--;
            team1->squad[index]->train();
            std::cout << "Training result:" << std::endl;
            team1->squad[index]->print();

            std::cout << std::endl;
            result = TrainingCentre;
            break;
        }
        case 5: {
            team2->printSquad();
            std::cout << "Select index of the player you want to buy:" << std::endl;
            int index2 = -1;
            std::cin >> index2;
            if (index2 < 0 || index2 >= team2->squad.size()) {
                std::cout << "Invalid index" << std::endl;
                result = TrainingCentre;
                break;
            }
            team1->printSquad();
            std::cout << "Select index player you want to let go:" << std::endl;
            int index = -1;
            std::cin >> index;
            if (index < 0 || index >= team1->squad.size()) {
                std::cout << "Invalid index" << std::endl;
                result = TrainingCentre;
                break;
            }

            team1->budget -= 5;
            team1->squad[index] = team2->squad[index2];
            team2->squad[index2] = nullptr;
            team1->start = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
            std::sort(team1->squad.begin(), team1->squad.end(), [](Player *a, Player *b) { return a->getPosition() < b->getPosition(); });
            result = TrainingCentre;
            break;
        }
        case 6: {
            result = ProceedToTheNextWeek;
            break;
        }
        default: {
            result = TrainingCentre;
            break;
        }
    }

    return result;
}

GameState proceedToTheMatch(Team *team1, Team *team2) {
    const std::array<int, 4> pow1 = team1->getPower();
    const std::array<int, 4> pow2 = team2->getPower();
    std::array<int, 2> score = {0, 0};
    int ball = 0;
    for (int minute = 0; minute < 90; minute++) {
        int sum = 0;
        int r = 0;
        switch (ball) {
            case 0: {
                sum = pow1[2] + pow2[2];
                r = rand() % (2 * sum);
                if (r < pow1[2]) {
                    ball++;
                } else if (r < sum) {
                    ball--;
                }
                break;
            }
            case 1: {
                sum = pow1[3] + pow2[1];
                r = rand() % (2 * sum);
                if (r < pow1[3]) {
                    ball++;
                } else if (r < sum) {
                    ball--;
                }
                break;
            }
            case 2: {
                sum = pow1[3] + pow2[0];
                r = rand() % (2 * sum);
                if (r < pow1[3]) {
                    ball++;
                } else if (r < sum) {
                    ball--;
                } else {
                    ball = 0;
                }
                break;
            }
            case 3: {
                score[0]++;
                ball = 0;
                break;
            }
            case -1: {
                sum = pow1[1] + pow2[3];
                r = rand() % (2 * sum);
                if (r < pow1[1]) {
                    ball++;
                } else if (r < sum) {
                    ball--;
                }
                break;
            }
            case -2: {
                sum = pow1[0] + pow2[3];
                r = rand() % (2 * sum);
                if (r < pow1[0]) {
                    ball++;
                } else if (r < sum) {
                    ball--;
                } else {
                    ball = 0;
                }
                break;
            }
            case -3: {
                score[1]++;
                ball = 0;
                break;
            }
            default: {
                break;
            }
        }
    }
    team1->history.push_back(team1->name + " " + std::to_string(score[0]) + " : " + std::to_string(score[1]) + " " + team2->name);
    std::cout << "Match result is" << std::endl;
    std::cout << team1->name + " " + std::to_string(score[0]) + " : " + std::to_string(score[1]) + " " + team2->name << std::endl;
    int sum1 = pow1[0] + pow1[1] + pow1[2] + pow1[3];
    int sum2 = pow2[0] + pow2[1] + pow2[2] + pow2[3];
    std::cout << team1->name << " total power is " << sum1 << std::endl;
    std::cout << team2->name << " total power is " << sum2 << std::endl;
    int f = 0;
    if (sum1 < sum2) {
        if (score[0] > score[1]) {
            f = 3;
        } else if (score[0] == score[1]) {
            f = 2;
        } else {
            f = -1;
        }
    } else if (sum1 > sum2) {
        if (score[0] > score[1]) {
            f = 1;
        } else if (score[0] == score[1]) {
            f = -1;
        } else {
            f = -2;
        }
    } else {
        if (score[0] > score[1]) {
            f = 2;
        } else if (score[0] == score[1]) {
            f = 0;
        } else {
            f = -1;
        }
    }
    team1->budget += f;
    std::cout << "You gain " << f << " points!" << std::endl;
    for (auto it = team1->squad.begin(); it != team1->squad.end(); ++it) {
        bool isSelected = false;
        for (int i = 0; i < 11; i++) {
            if (team1->start[i] == *it) {
                isSelected = true;
                (*it)->exhaust();
                break;
            }
        }
        if (!isSelected) {
            (*it)->rest();
        }
    }

    return TrainingCentre;
}
