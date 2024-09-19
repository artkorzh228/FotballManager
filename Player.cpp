#include "Player.h"
int Player::counter = 0;

Player::Player() {
    id = ++counter;
    name = "Player " + std::to_string(id);
    maxStamina = rand() % 20 + 1;
    stamina = maxStamina;
    strength = rand() % 20 + 1;
    speed = rand() % 20 + 1;
}

void Player::exhaust() {
    stamina--;
}

void Player::rest() {
    stamina = maxStamina;
}