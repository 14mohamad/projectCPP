#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <iostream>
#include "Board.hpp"
#include "Dice.hpp"
#include "Player.hpp"
class Game {
private:
    std::vector<Player> players;
    Board board;
    Dice dice;
    int currentPlayerIndex;

public:
    Game(const std::vector<std::string>& playerNames);
    void start();
    void playTurn();
    bool isGameOver() const;
    void displayGameState() const;
    void printWinner();
    std::vector<Player> getPlayers();
    int getCurrentPlayerIndex();
};

#endif // GAME_H
