#include "Board.hpp"
#include "Space.hpp"
// Constructor
Board::Board():spaces(), streets() {}

// Destructor
Board::~Board() {
    // Free dynamically allocated spaces
    // חללים שהוקצו באופן דינמי חינם
    for (auto space : spaces) {
        delete space;
    }
}

// Initialize the board with spaces
// אתחול הלוח עם רווחים
void Board::initialize(Game* game) {
    spaces.push_back(new Go("Go"));
    spaces.push_back(new Street("MEDITERRANEAN AVENUE", 60, 50, 100, 200, streets[0]));
    spaces.push_back(new CommunityChest("COMMUNITY CHEST"));
    spaces.push_back(new Street("BALTIC AVENUE", 60, 50, 100, 200, streets[0]));
    spaces.push_back(new IncomeTax("INCOME TAX"));
    spaces.push_back(new Train("READING RAILROAD" , 200));
    spaces.push_back(new Street("ORIENTAL AVENUE", 100, 50, 100, 200, streets[1]));
    spaces.push_back(new Chance("CHANCE", game));
    spaces.push_back(new Street("VERMONT AVENUE", 100, 50, 100, 200, streets[1]));
    spaces.push_back(new Street("CONNECTICUT AVENUE", 120, 50, 100, 200, streets[1]));
    
    spaces.push_back(new Jail("Jail"));
    spaces.push_back(new Street("ST.CHARLES PLACE", 140, 50, 100, 200, streets[2]));
    spaces.push_back(new ElectricCompany("ELECTRIC COMPANY"));
    spaces.push_back(new Street("STATES AVENUE", 140, 50, 100, 200, streets[2]));
    spaces.push_back(new Street("VIRGINIA AVENUE", 160, 50, 100, 200, streets[2]));
    spaces.push_back(new Train("PENNSYLVANIA RAILROAD", 200));
    spaces.push_back(new Street("ST.JAMES PLACE", 180, 50, 100, 200, streets[3]));
    spaces.push_back(new CommunityChest("COMMUNITY CHEST"));
    spaces.push_back(new Street("TENNESSE AVENUE", 180, 50, 100, 200, streets[3]));
    spaces.push_back(new Street("NEW YORK AVENUE", 200, 50, 100, 200, streets[3]));
    
    spaces.push_back(new FreeParking("Free Parking"));
    spaces.push_back(new Street("KENTUCKY AVENUE", 220, 50, 100, 200, streets[4]));
    spaces.push_back(new Chance("CHANCE", game));
    spaces.push_back(new Street("INDIANA AVENUE", 220, 50, 100, 200, streets[4]));
    spaces.push_back(new Street("ILLINOIS AVENUE", 240, 50, 100, 200, streets[4]));
    spaces.push_back(new Train("B.&O. RAILROAD", 200));
    spaces.push_back(new Street("ATLANTIC AVENUE", 260, 50, 100, 200, streets[5]));
    spaces.push_back(new Street("VENTNOR AVENUE", 260, 50, 100, 200, streets[5]));
    spaces.push_back(new WaterWorks("WATER WORKS"));
    spaces.push_back(new Street("MARVIN GARDENS", 280, 50, 100, 200, streets[5]));

    spaces.push_back(new GoToJail("Go To Jail"));
    spaces.push_back(new Street("PACIFIC AVENUE", 300, 50, 100, 200, streets[6]));
    spaces.push_back(new Street("NORTH CAROLINA AVENUE", 300, 50, 100, 200, streets[6]));
    spaces.push_back(new CommunityChest("COMMUNITY CHEST"));
    spaces.push_back(new Street("PENNSYLVANIA AVENUE", 320, 50, 100, 200, streets[6]));
    spaces.push_back(new Train("SHORT LINE", 200));
    spaces.push_back(new Chance("CHANCE", game));
    spaces.push_back(new Street("PARK PLACE", 350, 50, 100, 200, streets[7]));
    spaces.push_back(new LuxuryTax("LUXURY TAX"));
    spaces.push_back(new Street("BOARDWALK", 400, 50, 100, 200, streets[7]));
}

// Get space by index
// קבל מקום לפי אינדקס
Space* Board::getSpace(int index) {
    if (index >= 0 && (unsigned int)index < spaces.size()) {
        return spaces[index];
    }
    return nullptr;
}

// Get index space by name
// קבל שטח אינדקס לפי שם
int Board::getSpaceIndex(std::string name){
    for(unsigned int i = 0; i < spaces.size(); i++){
        if(spaces[i]->getLabel() == name){
            return i;
        }
    }
    return -1;
}

std::vector<Space*> Board::getSpaces(){
    return spaces;
}
