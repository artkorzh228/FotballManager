#include "Midfielder.h"

#include <iostream>

Midfielder::Midfielder() {
    shortPass = rand() % 20 + 1;
    longPass = rand() % 20 + 1;
    position = 2;
}

void Midfielder::train() {
    if (stamina == 0) {
        return;
    }
    const int type = rand() % 5 + 1;
    const int level = rand() % 20 + 1;
    switch (type) {
        case 1:
            if (level > shortPass) {
                shortPass++;
                stamina--;
            }
        break;
        case 2:
            if (level > longPass) {
                longPass++;
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

void Midfielder::print() {
    std::cout << "Mdf " << name << ". Stamina: " << stamina << ", Strength: " << strength << ", Speed: " << speed << ", Short pass: " << shortPass << ", Long Pass: " << longPass;
}

void Midfielder::save(std::ostream &os) {
    os << name << std::endl << id << " " << maxStamina << " " << stamina << " " << strength << " " << speed << " " << shortPass << " " << longPass << std::endl;
}

void Midfielder::load(std::istream &is) {
    std::getline(is, name);
    is >> id >> maxStamina >> stamina >> strength >> speed >> shortPass >> longPass;
    if (id > Player::counter) {
        Player::counter = id;
    }
}

int Midfielder::getPower() {
    return (2 * shortPass) + (2 * longPass) + ((strength + speed) / 2);
}

int Midfielder::getPosition() {
    return position;
}