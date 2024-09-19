#include "Defender.h"

#include <iostream>
#include <ostream>

Defender::Defender() {
    tackle = rand() % 20 + 1;
    interception = rand() % 20 + 1;
    position = 1;
}


void Defender::train() {
    if (stamina == 0) {
        return;
    }
    const int type = rand() % 5 + 1;
    const int level = rand() % 20 + 1;
    switch (type) {
        case 1:
            if (level > tackle) {
                tackle++;
                stamina--;
            }
        break;
        case 2:
            if (level > interception) {
                interception++;
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

void Defender::print() {
    std::cout << "Def " << name << ". Stamina: " << stamina << ", Strength: " << strength << ", Speed: " << speed << ", Tackle: " << tackle << ", Interception: " << interception;
}

void Defender::save(std::ostream &os) {
    os << name << std::endl << id << " " << maxStamina << " " << stamina << " " << strength << " " << speed << " " << tackle << " " << interception << std::endl;
}

void Defender::load(std::istream &is) {
    std::getline(is, name);
    is >> id >> maxStamina >> stamina >> strength >> speed >> tackle >> interception;
    if (id > Player::counter) {
        Player::counter = id;
    }
}

int Defender::getPower() {
    return (2 * tackle) + (2 * interception) + ((3 * strength + speed) / 4);
}

int Defender::getPosition() {
    return position;
}
