#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Game.hpp"
class GUI {
private:
    // מרקם לרקע
    sf::Texture backgroundTexture; // Texture for the background
    // Sprite כדי להציג את הרקע
    sf::Sprite backgroundSprite;    // Sprite to display the background

public:
    sf::RenderWindow window;
    GUI();
    // פונקציה לעיבוד מצב המשחק
    void render(std::vector<Player> players); // Function to render the game state
    // פונקציה לטיפול בקלט משתמש
    void handleEvents(); // Function to handle user input
    // פונקציה לצייר את לוח המשחק
    void drawBoard(); // Function to draw the game board
    // פונקציה לצייר שחקנים
    void drawPlayers(std::vector<Player> players); // Function to draw players
};

#endif // GUI_H
