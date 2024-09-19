#include "Forward.h"

#include <iostream>

Forward::Forward() {
    shot = rand() % 20 + 1;
    dribbling = rand() % 20 + 1;
    position = 3;
}

void Forward::train() {
    if (stamina == 0) {
        return;
    }
    const int type = rand() % 5 + 1;
    const int level = rand() % 20 + 1;
    switch (type) {
        case 1:
            if (level > shot) {
                shot++;
                stamina--;
            }
        break;
        case 2:
            if (level > dribbling) {
                dribbling++;
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

void Forward::print() {
    std::cout << "Fwd " << name << ". Stamina: " << stamina << ", Strength: " << strength << ", Speed: " << speed << ", Shot: " << shot << ", Dribbling: " << dribbling;
}

void Forward::save(std::ostream &os) {
    os << name << std::endl << id << " " << maxStamina << " " << stamina << " " << strength << " " << speed << " " << shot << " " << shot << std::endl;
}

void Forward::load(std::istream &is) {
    std::getline(is, name);
    is >> id >> maxStamina >> stamina >> strength >> speed >> shot >> dribbling;
    if (id > Player::counter) {
        Player::counter = id;
    }
}

int Forward::getPower() {
    return (2 * shot) + (2 * dribbling) + ((strength + (3 * speed)) / 4);
}

int Forward::getPosition() {
    return position;
}