#include "Player.hpp"
#include "Space.hpp"
#include "Board.hpp"
// Player constructor
Player::Player(std::string name, Board& board, sf::Color playerColor)
    : name(name), board(board), outOfJailCard(false), jailed(false), bankrupt(false), money(1500), trains(0), currentPosition(0), color(playerColor) {}

// Get the player's name
std::string Player::getName() const {
    return name;
}

// Move the player by a certain number of steps
// הזיזו את הנגן במספר מסוים של צעדים
void Player::move(int steps) {
    /*
     // Implement logic for moving the player
 ‎    // יישם היגיון להזזת השחקן
     // This typically involves updating the player's position on the board
 ‎    // זה כרוך בדרך כלל בעדכון מיקומו של השחקן על הלוח

     */
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
        bankrupt = true;
        for(auto& space: spaces){
            space->leaveSpace();
        }
    }
}

// Go to a specific space by name
// עבור למרחב מסוים לפי שם
void Player::goTo(std::string spaceName) {
    move(currentPosition - board.getSpaceIndex(spaceName));
}

// Go to Jail
// לך לכלא
void Player::goToJail() {
    jailed = true;
    move(currentPosition - board.getSpaceIndex("Jail"));
}

// Go to Utility
// עבור אל Utility
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
// לך לרכבת
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
// קבל את המרחבים בבעלות השחקן
std::vector<Space*> Player::getSpaces() {
    return spaces;
}

// Set whether the player has an out-of-jail card
// הגדר אם לשחקן יש כרטיס מחוץ לכלא
void Player::setOutOfJailCard(bool card) {
    outOfJailCard = card;
}

// Check if the player has an out-of-jail card
// בדוק אם לשחקן יש כרטיס מחוץ לכלא
bool Player::getOutOfJailCard() {
    return outOfJailCard;
}

// Get the player's current amount of money
// קבל את סכום הכסף הנוכחי של השחקן
int Player::getMoney() const {
    return money;
}

// Calculate rent from owned trains
// חשב שכר דירה מרכבות בבעלות
int Player::trainsRent() {
    // Implement logic for calculating rent based on the number of owned trains
    // יישום היגיון לחישוב שכר דירה על בסיס מספר הרכבות בבעלות
    return trains * 50;
}

// Check if the player is jailed
// בדוק אם השחקן כלוא
bool Player::isJailed() {
    return jailed;
}

void Player::freeFromJail(){
    jailed = false;
}

bool Player::isBankrupt() const{
    return bankrupt;
}

unsigned int Player::getPosition() const{
    return currentPosition;
}

sf::Color Player::getColor() const {
    return color;
}
