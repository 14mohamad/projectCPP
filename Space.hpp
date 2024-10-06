#ifndef SPACE_H
#define SPACE_H

#include <string>
#include <iostream>
#include <cmath>

class Player;
class Game;
class Space {
public:
    Space(const std::string& label, bool utility, bool railroad);
    virtual ~Space() = default;
    // Pure virtual function
    virtual void visit(Player& player) = 0;
    bool isOwned();
    Player* getOwner();
    void setOwner(Player* player);
    bool isUtility();
    bool isRailroad();
    std::string getLabel();
    virtual int getRepairs() = 0;
    virtual int getStreetRepairs() = 0;
    
private:
    std::string label;
    Player* owner;
    bool ownedSpace;
    bool utility;
    bool railroad;
};

class Chance : public Space {
private:
    Game* game;
public:
    Chance(const std::string& name, Game* game);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};

class Street : public Space {
private:
    struct StreetGroup& StreetGroup;
    int price;
    int rent;
    int houses;
    int hotels;
    int housePrice;
    int hotelPrice;

public:
    Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct StreetGroup& streetGroup);
    void visit(Player& player) override;
    void buildHouse(Player& player);
    int getRent() const;
    int getRepairs() override;
    int getStreetRepairs() override;
};

class Train : public Space {
private:
    int price;

public:
    Train(const std::string& name, int price);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};


class Go : public Space {
private:
public:
    Go(const std::string& name);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};


class Jail : public Space {
private:
public:
    Jail(const std::string& name);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};

class GoToJail : public Space {
private:
public:
    GoToJail(const std::string& name);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};


class FreeParking: public Space {
private:
public:
    FreeParking(const std::string& name);
    void visit(Player& player) override;
    int getRepairs() override;
    int getStreetRepairs() override;
};


#endif // SPACE_H