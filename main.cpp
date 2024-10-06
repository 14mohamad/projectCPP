#include <iostream>
#include <vector>
#include "Game.hpp"

int main() {
    std::vector<std::string> playerNames;
    int numPlayers;

    std::cout << "Enter number of players: ";
    std::cin >> numPlayers;
    
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Enter name for player " << (i + 1) << ": ";
        std::cin >> name;
        playerNames.push_back(name);
    }

    Game game(playerNames);
    game.start(); // Start the game

    return 0;
}
