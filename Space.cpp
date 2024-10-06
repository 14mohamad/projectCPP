#include "Space.hpp"
#include "Player.hpp"
#include "Game.hpp"

// Space constructor
Space::Space(const std::string& label, bool utility, bool railroad)
    : label(label), utility(utility), railroad(railroad), ownedSpace(false), owner(nullptr) {}

// Check if the space is owned
bool Space::isOwned() {
    return ownedSpace;
}

// Get the owner of the space
Player* Space::getOwner() {
    return owner;
}
void Space::setOwner(Player* player){
    owner = player;
    ownedSpace = true;
}
// Check if the space is a utility
bool Space::isUtility() {
    return utility;
}

// Check if the space is a railroad
bool Space::isRailroad() {
    return railroad;
}
std::string Space::getLabel(){
    return label;
}
// Chance constructor
Chance::Chance(const std::string& name, Game* game)
    : Space(name, false, false), game(game) {}

// Visit function for Chance space
void Chance::visit(Player& player) {
    std::cout << player.getName() << " visited chance." << std::endl;
    int randomChance = rand() % 16;
    switch (randomChance)
    {
    case 0: //Advance to Go (Collect $200)
        std::cout << player.getName() << " has advanced to go." << std::endl;
        player.move(0);
        break;
    case 1: //Bank pays you dividend of $50
        std::cout << player.getName() << " Bank pays you dividend of $50." << std::endl;
        player.collect(50);
        break;
    case 2: //Go back 3 spaces
        std::cout << player.getName() << " Go back 3 spaces." << std::endl;
        player.move(-3);
        break;
    case 3: //Go directly to Jail – do not pass Go, do not collect $200
        std::cout << player.getName() << " Go directly to Jail – do not pass Go, do not collect $200." << std::endl;
        player.goToJail();
        break;
    case 4: //Make general repairs on all your property – For each house pay $25 – For each hotel $100
        std::cout << player.getName() << " Make general repairs on all your property – For each house pay $25 – For each hotel $100." << std::endl;
        int repairs = 0;
        for(auto& space: player.getSpaces()){
            repairs = repairs + space.getRepairs();
        }
        player.pay(repairs);
        break;
    case 5: //Pay poor tax of $15
        std::cout << player.getName() << " Pay poor tax of $15." << std::endl;
        player.pay(15);
        break;
    case 6: //Take a trip to Reading Railroad – If you pass Go collect $200
        std::cout << player.getName() << " Take a trip to Reading Railroad – If you pass Go collect $200." << std::endl;
        player.goTo("READING RAILROAD");
        break;
    case 7: //Take a walk on the Boardwalk – Advance token to Boardwalk
        std::cout << player.getName() << " Take a walk on the Boardwalk – Advance token to Boardwalk." << std::endl;
        player.goTo("BOARDWALK");
        break;
    case 8: //You have been elected Chairman of the Board – Pay each player $50
        std::cout << player.getName() << " You have been elected Chairman of the Board – Pay each player $50." << std::endl;
        for(auto& p: game.getPlayer()){
            if(player.getName != p.getName()){
                p.collect(50);
                p.pay(50);
            }
        }
        break;
    case 9: //Your building loan matures – Collect $150
        std::cout << player.getName() << " Your building loan matures – Collect $150." << std::endl;
        player.pay(150);
        break;
    case 10: //Get out of Jail Free – This card may be kept until needed or traded
        std::cout << player.getName() << " Get out of Jail Free – This card may be kept until needed or traded." << std::endl;
        player.setOutOfJailCard(true);
        break;
    case 11: //Advance to Illinois Ave. – If you pass Go, collect $200
        std::cout << player.getName() << " Advance to Illinois Ave. – If you pass Go, collect $200." << std::endl;
        player.goTo("ILLINOIS AVE");
        break;
    case 12: //Advance to St. Charles Place – If you pass Go, collect $200
        std::cout << player.getName() << " Advance to St. Charles Place – If you pass Go, collect $200." << std::endl;
        player.goTo("ST. CHARLES PLACE");
        break;
    case 13: //You are assessed for street repairs – $40 per house, $115 per hotel
        std::cout << player.getName() << " You are assessed for street repairs – $40 per house, $115 per hotel." << std::endl;
        int repairs = 0;
        for(auto& space: player.getSpaces()){
            repairs = repairs + space.getStreetRepairs();
        }
        player.pay(repairs);
        break;
    case 14: //Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.
        std::cout << player.getName() << " Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown." << std::endl;
        player.goToUtility();
        break;
    case 15: //Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled.
        std::cout << player.getName() << " Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled." << std::endl;
        player.goToRailroad();
        break;
    default:
        break;
    }
}

int Chance::getRepairs() {
    return 0;
}
int Chance::getStreetRepairs() {
    return 0;
}

// Street constructor
Street::Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct StreetGroup& StreetGroup)
    : Space(name, false, false), price(price), rent(rent), houses(0), hotels(0), housePrice(housePrice), hotelPrice(hotelPrice), StreetGroup(StreetGroup) {}

// Visit function for Street space
void Street::visit(Player& player) {
    std::cout << player.getName() << " has visited " << getLabel() << std::endl;
    if(isOwned() && getOwner()->getName() != player.getName()){ //the owner didn't visit
        std::cout << getLabel() << " is owned by " << getOwner()->getName() << " and " << player.getName() << " has to pay rent." << std::endl;
        int rentPrice = rent * std::pow(2, houses) * std::pow(16, hotels);
        player.pay(rentPrice);
        getOwner()->collect(rentPrice);
        std::cout << player.getName() << " paid " << rentPrice << " as rent." << std::endl;
        return;
    }
    if(isOwned()){ //the owner visited
        for(auto& street: StreetGroup){
            if(!street->isOwned() || street->getOwner() != player.getName()){
                std::cout << "You don't own the entire street, so you can't build houses." << std::endl;
                return;
            }
        }
        buildHouse(player);
        return;
    }
    //unowned
    std::cout << "This street is unowned, would you like to purchase it? (Y/N)" << std::endl;
    std::string input;
    std::cin >> input;
    if(input == "y"){
        if(player.getMoney() <= price){
            player.pay(price);
            setOwner(&player);
            return;
        }
        std::cout << "You dont have enough money to purchase this street." << std::endl;
    }
    std::cout << "The street wasn't purchased." << std::endl;
}

int Street::getRepairs() {
    return 25 * houses + 100 * hotels;
}
int Street::getStreetRepairs() {
    return 40 * houses + 115 * hotels;
}

// Build a house on the street
void Street::buildHouse(Player& player) {
    if(houses == 4){
        std::cerr << "Would you like to upgrade the houses to a hotel?" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.getMoney() >= hotelPrice){
                player.pay(hotelPrice);
                houses = 0;
                hotels++;
            } else {
                std::cout << "You can't afford this a hotel upgrade!" << std::endl;
            }
        }
        return;
    }
    std::cout << "Would you like to purchase a house? (y/n)" << std::endl;
    std::string input;
    std::cin >> input;
    if(input == "y"){
        if(player.getMoney() >= housePrice){
            player.pay(housePrice);
            houses++;
        } else {
            std::cerr << "You can't afford a house!" << std::endl;
        }
    }
}

// Get the rent for the street
int Street::getRent() const {
    return rent; // You might want to adjust this based on houses/hotels
}

// Train constructor
Train::Train(const std::string& name, int price)
    : Space(name, false, true), price(price) {}

// Visit function for Train space
void Train::visit(Player& player) {
    std::cout << player.getName() << " has visited " << getLabel() << std::endl;
    if(isOwned() && getOwner()->getName() != player.getName()){ //the owner didn't visit
        std::cout << getLabel() << " is owned by " << getOwner()->getName() << " and " << player.getName() << " has to pay rent." << std::endl;
        int rentPrice = getOwner()->trainsRent();
        player.pay(rentPrice);
        getOwner()->collect(rentPrice);
        std::cout << player.getName() << " paid " << rentPrice << " as rent." << std::endl;
        return;
    }
    //unowned
    if(!isOwned()){
        std::cout << "This train is unowned, would you like to purchase it? (Y/N)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.getMoney() <= price){
                player.pay(price);
                setOwner(&player);
                return;
            }
            std::cout << "You dont have enough money to purchase this streetraint." << std::endl;
        }
        std::cout << "The street wasn't purchased." << std::endl;
    }
}

int Train::getRepairs() {
    return 0;
}
int Train::getStreetRepairs() {
    return 0;
}

// Go constructor
Go::Go(const std::string& name)
    : Space(name, false, false) {}

// Visit function for Go space
void Go::visit(Player& player) {
    std::cout << player.getName() << " has visited " << getLabel() << " and collected $200!" << std::endl;
    player.collect(200);
}

int Go::getRepairs() {
    return 0;
}
int Go::getStreetRepairs() {
    return 0;
}

// Jail constructor
Jail::Jail(const std::string& name)
    : Space(name, false, false) {}

// Visit function for Jail space
void Jail::visit(Player& player) {
    if(!player.isJailed()){
        std::cout << player.getName() << " has visited " << getLabel() << std::endl;
        if(player.getOutOfJailCard()){
            std::cout <<  "You skipped jail time." << std::endl;
            player.setOutOfJailCard(false);
            return;
        }
        std::cout << "You got jailed!" << std::endl;
        return;
    }
    std::cout << "You are in jail, you need to roll a double to get out!" << std::endl;
}

int Jail::getRepairs() {
    return 0;
}
int Jail::getStreetRepairs() {
    return 0;
}

// GoToJail constructor
GoToJail::GoToJail(const std::string& name)
    : Space(name, false, false) {}

// Visit function for GoToJail space
void GoToJail::visit(Player& player) {
    std::cout << player.getName() << " has visited " << getLabel() << std::endl;
    player.goToJail();
}

int GoToJail::getRepairs() {
    return 0;
}
int GoToJail::getStreetRepairs() {
    return 0;
}

// FreeParking constructor
FreeParking::FreeParking(const std::string& name)
    : Space(name, false, false) {}

// Visit function for Free Parking space
void FreeParking::visit(Player& player) {
    std::cout << player.getName() << " has visited " << getLabel() << std::endl;
}

int FreeParking::getRepairs() {
    return 0;
}
int FreeParking::getStreetRepairs() {
    return 0;
}