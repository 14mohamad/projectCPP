#include "GUI.hpp"
#include <string>
#include <sstream>

GUI::GUI() : window(sf::VideoMode(900,900), "Monopoly") {
    if (!backgroundTexture.loadFromFile("board.jpeg")) {
        std::cerr << "Could not load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    float targetWidth = 900.f;
    float targetHeight = 900.f;

    float scaleX = targetWidth / backgroundTexture.getSize().x; // Width scale
    float scaleY = targetHeight / backgroundTexture.getSize().y; // Height scale

    backgroundSprite.setScale(scaleX, scaleY);
    
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GUI::render(std::vector<Player> players) {
    window.clear();
    // צייר את תמונת הרקע
    window.draw(backgroundSprite); // Draw the background image
    drawPlayers(players);
    window.display();
}

void GUI::drawBoard() {
    // Load and draw the game board here (replace with actual drawing logic)
    // טען וצייר את לוח המשחק כאן (החלף בהיגיון ציור בפועל)
    sf::RectangleShape board(sf::Vector2f(600, 600));
    board.setFillColor(sf::Color::Green);
    window.draw(board);
}

void GUI::drawPlayers(std::vector<Player> players) {
    // Loop through each player to draw their position
    // עברו בלולאה בין כל שחקן כדי לצייר את המיקום שלו
    for (const auto& player : players) {
        // קבל את המיקום הנוכחי של השחקן
        unsigned int position = player.getPosition(); // Get player's current position
        int x = 0, y = 0;
        int gap = 75;
        // Determine x and y based on the position, moving clockwise
        // קבע את x ו-y על סמך המיקום, נעים בכיוון השעון
        if (position > 0 && position <= 9) { // Bottom row (0 to 9)
            // מרכז כל חלל
            x = 900 - (position * gap + gap); // Center of each space
            // גובה קבוע עבור השורה התחתונה
            y = 900 - gap; // Fixed height for the bottom row
        } else if (position > 10 && position <= 18) { // Right column (10 to 18)
            x = gap/2; // Fixed width for the right column
            y = 900 - ((position - 10) * gap + gap); // Center of each space
        } else if (position > 19 && position <= 28) { // Top row (19 to 28)
            x = (28 - position) * gap + gap; // Reverse indexing
            y = gap/2; // Fixed height for the top row
        } else if (position > 29 && position <= 37) { // Left column (29 to 37)
            x = 900-gap; // Fixed width for the left column
            y = (position - 29) * gap + gap; // Center of each space
        } else if(position == 0){
            x = 840;
            y = 840;
        } else if(position == 10){
            x = 55;
            y = 840;
        } else if(position == 19){
            x = 55;
            y = 55;
        } else if(position == 29){
            x = 840;
            y = 55;
        }

        // Create a colored circle for the player
        // צור עיגול צבעוני עבור השחקן
        sf::CircleShape playerBall(15); // Radius of 15 pixels
        // השתמש בצבע הראשי
        playerBall.setFillColor(player.getColor()); // Use the primary color
        playerBall.setPosition(x, y); // Set position based on calculated x and y
        // צייר את כדור השחקן
        window.draw(playerBall); // Draw the player ball
    }   
}
