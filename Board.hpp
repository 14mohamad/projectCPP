#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
class Space;
class Game;
class Board {
private:
    // אוסף רווחים על הלוח
    std::vector<Space*> spaces; // Collection of spaces on the board
    std::vector<Space*> streets[8];

public:
    Board();
    // הרס לניקוי חללים שהוקצו באופן דינמי
    ~Board(); // Destructor to clean up dynamically allocated spaces

    // אתחול הלוח עם רווחים
    void initialize(Game* game); // Initialize the board with spaces
    // קבל מקום לפי אינדקס
    Space* getSpace(int index); // Get space by index
    // קבל שטח אינדקס לפי שם
    int getSpaceIndex(std::string name); // Get index space by name
    std::vector<Space*> getSpaces();
};	

#endif // BOARD_H
