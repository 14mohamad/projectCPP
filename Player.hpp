#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
class Space;
class Player {
private:
    std::string name;
    std::vector<Space*> spaces;
    bool outOfJailCard;
    bool jailed;
    int money;
    int trains;
public:
    Player(std::string name);
    std::string getName();
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
    int getMoney();
    int trainsRent();
    bool isJailed();
};

#endif // PLAYER_H
