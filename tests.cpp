#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "Game.hpp"
#include "Space.hpp"

using namespace std;

TEST_CASE("Test Board functionality") {
    Board board;
    board.initialize(nullptr); // Initialize with nullptr for game reference

    // Create some properties to test
    std::vector<Space*> group;
    Street* property1 = new Street("Mediterranean Avenue", 100, 6, 50, 200, group);
    Street* property2 = new Street("Baltic Avenue", 100, 6, 50, 200, group);

    board.getSpaces().push_back(property1);
    board.getSpaces().push_back(property2);

    CHECK(board.getSpaces().size() == 2);
    CHECK(board.getSpace(0)->getLabel() == "Mediterranean Avenue");
    CHECK(board.getSpace(1)->getLabel() == "Baltic Avenue");

    // Cleanup
    delete property1;
    delete property2;
}

TEST_CASE("Test Player functionality") {
    Board board;
    Player player("Alice", board, sf::Color::Red);

    CHECK(player.getName() == "Alice");
    CHECK(player.getMoney() == 1500); // Assuming default money is 1500
    CHECK(player.isBankrupt() == false);
    CHECK(player.getSpaces().empty());

    // Move the player and check position
    player.move(5);
    CHECK(player.getPosition() == 5);

    // Simulate collecting and paying money
    player.collect(200);
    CHECK(player.getMoney() == 1700); // After collecting 200

    player.pay(100);
    CHECK(player.getMoney() == 1600); // After paying 100
}

TEST_CASE("Test Game functionality") {
    Game game({"Alice", "Bob"});

    CHECK(game.getPlayers().size() == 2);
    CHECK(game.getPlayers()[0].getName() == "Alice");
    CHECK(game.getPlayers()[1].getName() == "Bob");

    game.start(); // Start the game

    CHECK(game.isGameOver() == false);

    game.playTurn(); // Simulate a turn for the current player
    CHECK(game.getCurrentPlayerIndex() == 1); // Check that the next player's turn is correct
}

TEST_CASE("Test Dice functionality") {
    Dice dice;

    for (int i = 0; i < 100; ++i) { // Roll dice multiple times for testing
        dice.roll();
        int total = dice.getTotal();
        CHECK(total >= 2 && total <= 12); // Dice roll should be between 2 and 12
        CHECK(dice.isDouble() == (dice.getFirstDie() == dice.getSecondDie()));
    }
}

TEST_CASE("Test Space functionality") {
    Board board;
    Player player("Alice", board, sf::Color::Red);
    std::vector<Space*> group;
    Space* property = new Street("Mediterranean Avenue", 100, 6, 50, 200, group);
    board.getSpaces().push_back(property);

    CHECK(property->isOwned() == false);
    
    property->setOwner(&player);
    CHECK(property->getOwner()->getName() == "Alice");
    CHECK(property->isOwned() == true);

    // Simulate player landing on property
    property->visit(player);
    CHECK(player.getMoney() < 1500); // Assume rent or costs are deducted
    CHECK(property->getRepairs() == 0); // Assume no repairs for new property

    // Clean up
    delete property;
}

TEST_CASE("Test Invalid Game State") {
    Game game({}); // No players

    CHECK_THROWS_AS(game.start(), runtime_error); // Should throw error when starting without players
}
