#include "Goalkeeper.h"

#include <iostream>

Goalkeeper::Goalkeeper() {
    goalkeeping = rand() % 20 + 1;
    reaction = rand() % 20 + 1;
    position = 0;
}

void Goalkeeper::train() {
    if (stamina == 0) {
        return;
    }
    const int type = rand() % 5 + 1;
    const int level = rand() % 20 + 1;
    switch (type) {
        case 1:
            if (level > goalkeeping) {
                goalkeeping++;
                stamina--;
            }
        break;
        case 2:
            if (level > reaction) {
                reaction++;
                stamina--;
            }
        break;
        case 3:
            if (level > maxStamina) {
                maxStamina++;
                stamina--;
            }
        break;
        case 4:
            if (level > strength) {
                strength++;
                stamina--;
            }
        break;
        case 5:
            if (level > speed) {
                speed++;
                stamina--;
            }
        break;
        default:
            break;
    }
}

void Goalkeeper::print() {
    std::cout << "Gkp " << name << ". Stamina: " << stamina << ", Strength: " << strength << ", Speed: " << speed << ", Goalkeeping: " << goalkeeping << ", Reaction: " << reaction;
}

void Goalkeeper::save(std::ostream &os) {
    os << name << std::endl << id << " " << maxStamina << " " << stamina << " " << strength << " " << speed << " " << goalkeeping << " " << reaction << std::endl;
}

void Goalkeeper::load(std::istream &is) {
    std::getline(is, name);
    is >> id >> maxStamina >> stamina >> strength >> speed >> goalkeeping >> reaction;
    if (id > Player::counter) {
        Player::counter = id;
    }
}

int Goalkeeper::getPower() {
    return (2 * goalkeeping) + (2 * reaction) + ((speed + strength) / 2);
}

int Goalkeeper::getPosition() {
    return position;
}