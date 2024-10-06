#include "Player.hpp"
#include "Space.hpp"
#include "Board.hpp"
// Player constructor
Player::Player(std::string name, Board& board) 
    : name(name), board(board), outOfJailCard(false), jailed(false), bankrupt(false), money(1500), trains(0), currentPosition(0) {}

// Get the player's name
std::string Player::getName() const {
    return name;
}

// Move the player by a certain number of steps
void Player::move(int steps) { 
    // Implement logic for moving the player
    // This typically involves updating the player's position on the board
    currentPosition = currentPosition + steps;
    if(currentPosition > board.getSpaces().size()){
        std::cout << "You have passed Go and received $200" << std::endl;
        collect(200);
        currentPosition = currentPosition % board.getSpaces().size();
    } else if(currentPosition < 0){
        currentPosition = currentPosition + board.getSpaces().size();
    }
    Space* landedSpace = board.getSpace(currentPosition);
    if (landedSpace) {
        landedSpace->visit(*this);
    }
}

// Collect money
void Player::collect(int amount) {
    money += amount;
}

// Pay money
void Player::pay(int amount) {
    if (money >= amount) {
        money -= amount;
    } else {
        for(auto& space: spaces){
            space->leaveSpace();
        }
    }
}

// Go to a specific space by name
void Player::goTo(std::string spaceName) {
    move(currentPosition - board.getSpaceIndex(spaceName));
}

// Go to Jail
void Player::goToJail() {
    jailed = true;
    move(currentPosition - board.getSpaceIndex("Jail"));
}

// Go to Utility
void Player::goToUtility() {
    int steps = 0;
    for(unsigned int i = currentPosition + 1; i != currentPosition; i = (i + 1) % board.getSpaces().size()){
        steps++;
        if(board.getSpace(i)->isUtility()){
            move(steps);
            return;
        }
    }
}

// Go to Railroad
void Player::goToRailroad() {
    int steps = 0;
    for(unsigned int i = currentPosition + 1; i != currentPosition; i = (i + 1) % board.getSpaces().size()){
        steps++;
        if(board.getSpace(i)->isRailroad()){
            move(steps);
            return;
        }
    }
}

// Get the player's owned spaces
std::vector<Space*> Player::getSpaces() {
    return spaces;
}

// Set whether the player has an out-of-jail card
void Player::setOutOfJailCard(bool card) {
    outOfJailCard = card;
}

// Check if the player has an out-of-jail card
bool Player::getOutOfJailCard() {
    return outOfJailCard;
}

// Get the player's current amount of money
int Player::getMoney() const {
    return money;
}

// Calculate rent from owned trains
int Player::trainsRent() {
    // Implement logic for calculating rent based on the number of owned trains
    return trains * 50;
}

// Check if the player is jailed
bool Player::isJailed() {
    return jailed;
}

void Player::freeFromJail(){
    jailed = false;
}

bool Player::isBankrupt() const{
    return bankrupt;
}