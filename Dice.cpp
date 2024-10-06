#include "Dice.hpp"

Dice::Dice():die1(0), die2(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Dice::roll() {
    // Roll a die (1 to 6)
    int random = std::rand() % 36;
    die1 = random / 6 + 1;
    die2 = random % 6 + 1;
}

int Dice::getTotal() const {
    return die1 + die2;
}

bool Dice::isDouble() const {
    return die1 == die2;
}

int Dice::getFirstDie() const{
    return die1;
}
int Dice::getSecondDie() const{
    return die2;
}