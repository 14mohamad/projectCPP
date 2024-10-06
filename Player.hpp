#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
class Space;
class Board;
class Player {
private:
    std::string name;
    Board& board;
    std::vector<Space*> spaces;
    bool outOfJailCard;
    bool jailed;
    bool bankrupt;
    int money;
    int trains;
    unsigned int currentPosition;
public:
    Player(std::string name, Board& board);
    std::string getName() const;
    void move(int steps);
    void collect(int money);
    void pay(int money);
    void goTo(std::string spaceName);
    void goToJail();
    void goToUtility();
    void goToRailroad();
    std::vector<Space*> getSpaces();
    void setOutOfJailCard(bool card);
    bool getOutOfJailCard();
    int getMoney() const;
    int trainsRent();
    bool isJailed();
    void freeFromJail();
    bool isBankrupt() const;
};

#endif // PLAYER_H
