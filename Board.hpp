#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
class Space;
class Game;
class Board {
private:
    std::vector<Space*> spaces; // Collection of spaces on the board
    std::vector<Space*> streets[8];

public:
    Board();
    ~Board(); // Destructor to clean up dynamically allocated spaces

    void initialize(Game* game); // Initialize the board with spaces
    Space* getSpace(int index); // Get space by index
    int getSpaceIndex(std::string name); // Get index space by name
    std::vector<Space*> getSpaces();
};

#endif // BOARD_H
