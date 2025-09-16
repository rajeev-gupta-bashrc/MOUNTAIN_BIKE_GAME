#pragma once
#include <SFML/Graphics.hpp>
#include "bike_dynamics.hpp"
#include "terrain.hpp"

class Game {
public:
    Game();
    void run();

private:

    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    
    sf::RenderWindow window;
    Terrain terrain;
    Bike bike;
    
    sf::ConvexShape leftButton;
    sf::ConvexShape rightButton;

    sf::Font font;
    sf::Text gameWinText;
    sf::Text gameOverText;
    sf::Text restartText;
    
    bool gameWon;
    bool gameOver;
    
    void update(float deltaTime);
    void processEvents();
    void render();
    void createUI();
    void reset();
    bool checkGameOver() const; 
    

}; 