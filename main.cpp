#include <iostream>
#include <string>
#include <fstream>

#include "functions.h"
#include "Team.h"

int main() {
    std::string inputFileName;
    const char *outputFileName;

    int choice = startMenu();

    std::cout << "Enter the name of the file to be saved: " << std::endl;
    std::cin >> inputFileName;
    outputFileName = inputFileName.c_str();

    Team *team1;
    if (choice == 2) {
        std::ifstream inputFile;
        inputFile.open(outputFileName, std::ios::in);
        if (!inputFile.is_open()) {
            std::cout << "File could not be opened" << std::endl;
            return 1;
        }
        team1 = new Team();
        inputFile >> *team1;
        inputFile.close();
    } else {
        std::cout << "Enter your team name" << std::endl;
        std::string name;
        std::cin >> name;
        team1 = new Team(0, name);
    }

    GameState gameState = ProceedToTheNextWeek;
    int weekCounter = team1->history.size();
    Team *team2 = new Team();
    while (gameState != GameOver) {
        switch (gameState) {
            case ProceedToTheNextWeek: {
                delete team2;
                team2 = new Team(++weekCounter, "");
                gameState = BeforeMatch;
                break;
            }
            case BeforeMatch: {
                gameState = beforeMatch(team1, team2);
                break;
            }
            case OpponentInfo: {
                std::cout << "Opponent Info:" << std::endl;
                std::cout << team2->name << std::endl;
                std::cout << "Their tactic: " << std::endl;
                team2->printTactic();
                std::cout << "Their start 11: " << std::endl;
                team2->printStart();
                std::cout << "Their power: " << std::endl;
                team2->printPower();
                gameState = BeforeMatch;
                break;
            }
            case MySquad: {
                std::cout << "My Squad:" << std::endl;
                team1->printSquad();
                gameState = BeforeMatch;
                break;
            }
            case MyBudget: {
                std::cout << "My Budget:" << std::endl;
                std::cout << team1->budget << std::endl;
                gameState = BeforeMatch;
                break;
            }
            case MyStart11: {
                gameState = myStart11(team1);
                break;
            }
            case ProceedToTheMatch: {
                gameState = proceedToTheMatch(team1, team2);
                break;
            }
            case AfterMatch: {
                if (team1->budget < 0) {
                    gameState = GameOver;
                    break;
                }
                int g = 0, field = 0, d = 0, m = 0, s = 0;
                for (auto it = team1->squad.begin(); it != team1->squad.end(); ++it) {
                    if((*it)->stamina > 0) {
                        if ((*it)->getPosition() == 0) {
                            g++;
                        } else {
                            field++;
                            if ((*it)->getPosition() == 1) {
                                d++;
                            } else if ((*it)->getPosition() == 2) {
                                m++;
                            } else {
                                s++;
                            }
                        }
                    }
                }
                if (g == 0 || d == 0 || m == 0 || s == 0 || field < 10) {
                    gameState = GameOver;
                    break;
                }
                gameState = ProceedToTheNextWeek;
                break;
            }
            case SaveAndExit: {
                std::fstream outputFile;
                outputFile.open(outputFileName, std::ios::out);
                if (!outputFile.is_open()) {
                    std::cout << "File could not be opened" << std::endl;
                    gameState = GameOver;
                    break;
                }
                outputFile << (*team1);
                outputFile.close();
                gameState = GameOver;
                break;
            }
            case TrainingCentre: {
                gameState = trainingCentre(team1, team2);
                break;
            }
            case ChangePlayerName: {
                team1->printSquad();
                std::cout << "Select index of player:" << std::endl;
                int index = -1;
                std::cin >> index;
                if (index < 0 || index >= team1->squad.size()) {
                    std::cout << "Invalid index" << std::endl;
                    gameState = BeforeMatch;
                    break;
                }
                std::cout << "Input new name:" << std::endl;
                std::cin >> team1->squad[index]->name;
                gameState = BeforeMatch;
                break;
            }

            default: {
                gameState = GameOver;
                break;
            }
        }
    }
    std::cout << "Game Over :(" << std::endl;
    std::cout << "You succeeded for " << weekCounter << " weeks!!!" << std::endl;
    return 0;
}
