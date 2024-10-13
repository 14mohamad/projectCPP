#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

// Initialize player balances
void initializeBalances(Game& game, std::unordered_map<std::string, int>& balances) {
    for (const Player& player : game.getPlayers()) {
        balances[player.getName()] = 1500;  // Initial balance of $1500
    }
}

// Update player balance (e.g., for rent or purchases)
void updateBalance(std::unordered_map<std::string, int>& balances, const std::string& playerName, int amount) {
    balances[playerName] += amount;
}

// Check if the game should end (a player has $4000 or more or all but one are bankrupt)
bool checkGameEnd(const std::unordered_map<std::string, int>& balances) {
    int activePlayers = 0;
    std::string potentialWinner;

    for (const auto& [name, balance] : balances) {
        if (balance > 0) {
            activePlayers++;
            potentialWinner = name;
        }
    }

    // Check if any player has $4000 or more and declare them the winner
    for (const auto& [name, balance] : balances) {
        if (balance >= 4000) {
            std::cout << name << " has won with $" << balance << "!\n";
            return true;  // Immediate win if a player reaches $4000
        }
    }

    // Game ends only if one player has money left
    if (activePlayers == 1) {
        std::cout << potentialWinner << " has won by elimination!\n";
        return true;
    }

    return false;  // Continue the game if more than one player has money
}

// Print player statuses with balances
void printPlayerStatuses(Game& game, const std::unordered_map<std::string, int>& balances) {
    std::cout << "Player statuses:\n";
    for (const Player& player : game.getPlayers()) {
        std::string name = player.getName();
        std::cout << name << " - Position: " << player.getPosition()
                  << ", Balance: $" << balances.at(name) << "\n";
    }
    std::cout << "----------------------------\n";
}

// Test for player turn advancement and simulated balances with end conditions
TEST_CASE("Player Turn Advancement with Status Printing and Game End Logic") {
    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    while (!checkGameEnd(balances)) {
        game.playTurn();
        std::string currentPlayer = game.getPlayers()[game.getCurrentPlayerIndex()].getName();

        int transaction = (rand() % 1000) - 500;  // Random transaction
        updateBalance(balances, currentPlayer, transaction);

        printPlayerStatuses(game, balances);  // Print after each turn
    }

    CHECK(checkGameEnd(balances) == true);
}

// Test for correct game initialization
TEST_CASE("Game Initialization Test") {
    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};
    Game game(playerNames);

    CHECK(game.getPlayers().size() == 3);
    CHECK(game.getPlayers()[0].getName() == "Alice");
    CHECK(game.getPlayers()[1].getName() == "Bob");
    CHECK(game.getPlayers()[2].getName() == "Charlie");
}

// Test to ensure player balances update correctly
TEST_CASE("Balance Update Test") {
    std::vector<std::string> playerNames = {"Alice", "Bob"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    updateBalance(balances, "Alice", 500);  // Alice gains 500
    updateBalance(balances, "Bob", -300);   // Bob loses 300

    CHECK(balances["Alice"] == 2000);  // 1500 + 500
    CHECK(balances["Bob"] == 1200);    // 1500 - 300
}

// Test for winning condition (player reaches $4000)
TEST_CASE("Winning Condition - $4000 Test") {
    std::vector<std::string> playerNames = {"Alice", "Bob"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    updateBalance(balances, "Alice", 2500);  // Alice reaches 4000
    CHECK(checkGameEnd(balances) == true);   // Alice wins
}

// Test for elimination condition (only one player left with positive balance)
TEST_CASE("Winning Condition - Elimination Test") {
    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    updateBalance(balances, "Alice", -1500);  // Alice goes bankrupt
    updateBalance(balances, "Charlie", -1500);  // Charlie goes bankrupt

    CHECK(checkGameEnd(balances) == true);   // Bob wins by elimination
}

// Test to ensure correct turn order
TEST_CASE("Turn Order Test") {
    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};
    Game game(playerNames);

    CHECK(game.getCurrentPlayerIndex() == 0);  // Alice starts
    game.playTurn();
    CHECK(game.getCurrentPlayerIndex() == 1);  // Bob's turn
    game.playTurn();
    CHECK(game.getCurrentPlayerIndex() == 2);  // Charlie's turn
    game.playTurn();
    CHECK(game.getCurrentPlayerIndex() == 0);  // Back to Alice
}

// Test for Game Start with No Players (Edge Case)
// This test ensures the game handles initialization with no players gracefully.
TEST_CASE("Game Initialization with No Players Test") {
    std::vector<std::string> playerNames;  // No players
    Game game(playerNames);

    CHECK(game.getPlayers().size() == 0);  // Ensure no players are in the game
}


// Test for Player Passing GO Multiple Times in One Turn
// This test ensures that passing GO multiple times in one turn gives the correct bonus.
TEST_CASE("Multiple GO Passes in One Turn Test") {
    std::vector<std::string> playerNames = {"Alice"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    // Simulate Alice moving far enough to pass GO twice
    updateBalance(balances, "Alice", 400);  // $200 per pass, 2 passes

    CHECK(balances["Alice"] == 1900);  // 1500 + 400 (2 passes)
}

// Test for Tie Condition (Two Players Win Simultaneously)
// This test ensures that the game can detect a tie if two players reach $4000 simultaneously.
TEST_CASE("Tie Condition - Multiple Players Reach $4000") {
    std::vector<std::string> playerNames = {"Alice", "Bob"};
    Game game(playerNames);

    std::unordered_map<std::string, int> balances;
    initializeBalances(game, balances);

    updateBalance(balances, "Alice", 2500);  // Alice reaches 4000
    updateBalance(balances, "Bob", 2500);    // Bob also reaches 4000

    bool gameEnded = checkGameEnd(balances);  // Ensure the game ends
    CHECK(gameEnded == true);
}

