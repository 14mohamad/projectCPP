# Monopoly Game

This is a simple text-based Monopoly game implemented in C++. The game features basic mechanics, including players, spaces, dice rolls, and a graphical user interface using SFML.

## Table of Contents

- **Getting Started**
- **Game Structure**
- **Classes and Functions**
  -  Board
  -  Dice
  -  Game
  -  GUI
  -  Player
  -  Space
- **Running the Game**
- **License**


## Getting Started

To compile and run the game, you need a C++ compiler and the SFML library. Make sure to install SFML and link it correctly with your project.


## Game Structure

The game consists of several classes that interact with each other to create the game environment. The key classes include:
 
- **`Board`**
  - Manages the game board and its spaces.
- **`Dice`**
  - Handles the rolling of dice.
- **`Game`**
  - Manages game flow and player turns.
- **`Player`**
  - Represents each player in the game.
- **`GUI`**
  - Provides graphical representation using SFML.
- **`Space`**
  - Represents various spaces on the board.

### Classes and Functions

### 1. Board

The `Board` class represents the Monopoly board and contains various spaces.


#### Functions

- **`Board()`->**
  - Constructor that initializes the board.
- **`~Board()`->**
  - Destructor to clean up dynamically allocated spaces.
- **`void initialize(Game* game)`->**
  - Initializes the board with spaces.
- **`Space* getSpace(int index)`->**
  - Retrieves a space by its index.
- **`int getSpaceIndex(std::string name)`->**
  - Returns the index of a space by its name.
- **`std::vector<Space*> getSpaces()`->**
  - Returns all spaces on the board.

---

### 2. Dice

The `Dice` class handles the rolling of two dice.


#### Functions

- **`Dice()`->**
  - Constructor that initializes the dice.
- **`void roll()`->**
  - Rolls the dice.
- **`int getTotal() const`->**
  - Returns the total value of both dice.
- **`int getFirstDie() const`->**
  - Returns the value of the first die.
- **`int getSecondDie() const`->**
  - Returns the value of the second die.
- **`bool isDouble() const`->**
  - Checks if the rolled dice are doubles.

---

### 3. Game

The `Game` class manages the overall game flow.


#### Functions

- **`Game(const std::vector<std::string>& playerNames)`->**
  - Constructor that initializes players.
- **`void start()`->**
  - Starts the game.
- **`void playTurn()`->**
  - Manages a player's turn.
- **`bool isGameOver() const`->**
  - Checks if the game is over.
- **`void displayGameState() const`->**
  - Displays the current state of the game.
- **`void printWinner()`->**
  - Prints the winner of the game.
- **`std::vector<Player> getPlayers()`->**
  - Returns the list of players.

---

### 3. Player

The `Player` class represents a player in the game.


#### Functions

- **`Player(std::string name, Board& board, sf::Color playerColor)`->**
  - Constructor that initializes a player.
- **`std::string getName() const`->**
  - Returns the player's name.
- **`void move(int steps)`->**
  - Moves the player by a certain number of steps.
- **`void collect(int money)`->**
  - Collects money.
- **`void pay(int money)`->**
  - Pays money.
- **`void goTo(std::string spaceName)`->**
  - Moves to a specified space.
- **`void goToJail()`->**
  - Sends the player to jail.
- **`std::vector<Space*> getSpaces()`->**
  - Returns the spaces owned by the player.
- **`void setOutOfJailCard(bool card)`->**
  - Sets the out of jail card status.
- **`bool getOutOfJailCard()`->**
  - Checks if the player has an out of jail card.
- **`int getMoney() const`->**
  - Returns the player's money.
- **`unsigned int getPosition() const`->**
  - Returns the player's current position on the board.
- **`sf::Color getColor() const`->**
  - Returns the player's color.

---

### 4. GUI

The `GUI` class handles the graphical interface using SFML.


#### Functions

- **`GUI()`->**
  - Constructor that sets up the game window.
- **`void render(std::vector<Player> players)`->**
  - Renders the current game state.
- **`void handleEvents()`->**
  - Handles user input events.
- **`void drawBoard()`->**
  - Draws the game board.
- **`void drawPlayers(std::vector<Player> players)`->**
  - Draws players on the board.

---

### 5. Space

The `Space` class is a base class for different types of spaces on the board.


#### Functions

- **`Space(const std::string& label, bool utility, bool railroad)`->**
  - Constructor that initializes a space.
- **`virtual void visit(Player& player) = 0`->**
  - Pure virtual function to define what happens when a player visits this space.
- **`bool isOwned()`->**
  - Checks if the space is owned.
- **`Player* getOwner()`->**
  - Gets the owner of the space.
- **`void setOwner(Player* player)`->**
  - Sets the owner of the space.
- **`void removeOwner()`->**
  - Removes the owner of the space.
- **`bool isUtility()`->**
  - Checks if the space is a utility.
- **`bool isRailroad()`->**
  - Checks if the space is a railroad.
- **`std::string getLabel()`->**
  - Returns the label of the space.
- **`virtual int getRepairs() = 0`->**
  - Pure virtual function to get repair costs.
- **`virtual int getStreetRepairs() = 0`->**
  - Pure virtual function to get street repair costs.
- **`virtual void leaveSpace() = 0`->**
  - Pure virtual function to define actions when leaving the space.


**Derived Classes**: Include `Chance`, `Street`, `Train`, `Go`, `Jail`, `GoToJail`, `FreeParking`, `CommunityChest`, `IncomeTax`, `ElectricCompany`, `WaterWorks`, and `LuxuryTax`, each implementing the pure virtual functions in specific ways.

---

## Running the Game

To run the game, compile the code and execute the binary.
