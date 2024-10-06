#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
class GUI {
private:
    sf::Texture backgroundTexture; // Texture for the background
    sf::Sprite backgroundSprite;    // Sprite to display the background

public:
    sf::RenderWindow window;
    GUI();
    void render(std::vector<Player> players); // Function to render the game state
    void handleEvents(); // Function to handle user input
    void drawBoard(); // Function to draw the game board
    void drawPlayers(std::vector<Player> players); // Function to draw players
};

#endif // GUI_H
