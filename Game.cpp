#include "Game.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Dice.hpp"
#include "GUI.hpp"
const std::vector<sf::Color> playerColors = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Cyan,
    sf::Color::White,
    sf::Color::Black
};
// Constructor that initializes the game with player names
// קונסטרוקטור המאתחל את המשחק עם שמות שחקנים
Game::Game(const std::vector<std::string>& playerNames) : currentPlayerIndex(0) {
    int i = 0;
    for (const auto& name : playerNames) {
        players.emplace_back(Player(name, board, playerColors[i]));
        i++;
    }
    board.initialize(this);
}

// Start the game loop
// התחל את לולאת המשחק
void Game::start() {
    GUI gui;
    // Main game loop
    // לולאת משחק ראשית
    while (gui.window.isOpen() && !isGameOver()) {
        gui.handleEvents();
        gui.render(players);
        playTurn();
        displayGameState();
    }
    
    std::cout << "Game over!" << std::endl;
    printWinner();
    gui.window.close();

}

// Play a turn for the current player
// שחק תור עבור השחקן הנוכחי
void Game::playTurn() {
    Player& currentPlayer = players[currentPlayerIndex];
    std::cout << currentPlayer.getName() << "'s turn." << std::endl;
    if(currentPlayer.isJailed()){
        std::cout << "You are currently in jail, you need to get a double!" << std::endl;
    }
    dice.roll();
    if(currentPlayer.isJailed() && dice.isDouble()){
        std::cout << "You rolled a double and got free!" << std::endl;
        currentPlayer.freeFromJail();
    }
    int steps = dice.getTotal();
    currentPlayer.move(steps);
    // עבור לשחקן הבא
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size(); // Move to the next player
}

// Check if the game is over
// בדוק אם המשחק נגמר
bool Game::isGameOver() const {
    int activePlayers = 0;
    for (const auto& player : players) {
        if(player.getMoney() >= 4000){
            return true;
        }
        if (!player.isBankrupt()) {
            activePlayers++;
        }
    }
    // המשחק נגמר אם שחקן אחד פעיל או לא
    return activePlayers <= 1; // Game over if one or no players are active
}

// Display the current state of the game
// הצג את המצב הנוכחי של המשחק
void Game::displayGameState() const {
    for (const auto& player : players) {
        std::cout << player.getName() << ": $" << player.getMoney()  << " current position: " << player.getPosition() << std::endl;
    }
}

void Game::printWinner(){
    int winner = 0;
    int index = 0;
    for (const auto& player : players) {
        if(player.getMoney() >= 4000){
            std::cout << player.getName() << " has won!" << std::endl;
            return;
        }
        if (!player.isBankrupt()) {
            winner = index;
        }
        index++;
    }
    std::cout << players[winner].getName() << " has won!" << std::endl;
}

std::vector<Player> Game::getPlayers(){
    return players;
}

int Game::getCurrentPlayerIndex(){
    return currentPlayerIndex;
}
