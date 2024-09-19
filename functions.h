#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "enums.h"
#include "Team.h"

int startMenu();
GameState myStart11(Team *team1);
GameState trainingCentre(Team *team1, Team *team2);
GameState proceedToTheMatch(Team *team1, Team *team2);
GameState beforeMatch(Team *team1, Team *team2);

#endif //FUNCTIONS_H
