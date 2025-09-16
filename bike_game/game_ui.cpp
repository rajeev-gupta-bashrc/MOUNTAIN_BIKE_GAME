#include "game_ui.hpp"
#include "terrain.hpp"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Bike Rider")
    , terrain(80.0f, 300.0f, 2000.0f)  // amplitude = 80, time period = 300, track length = 2000
    , bike(100.f, 200.f)  // Start in the middle of the flat section
    , gameWon(false)
    , gameOver(false)
{
    window.setFramerateLimit(60);
    createUI();
}



void Game::createUI() {
    float buttonSize = 50.f;
    
    leftButton = sf::ConvexShape(3);
    leftButton.setPoint(0, sf::Vector2f(buttonSize, 0.f));
    leftButton.setPoint(1, sf::Vector2f(buttonSize, buttonSize));
    leftButton.setPoint(2, sf::Vector2f(0.f, buttonSize/2.f));
    leftButton.setPosition(10.f, WINDOW_HEIGHT - buttonSize - 10.f);
    leftButton.setFillColor(sf::Color(200, 200, 200));
    
    
    rightButton = sf::ConvexShape(3);
    rightButton.setPoint(0, sf::Vector2f(0.f, 0.f));
    rightButton.setPoint(1, sf::Vector2f(0.f, buttonSize));
    rightButton.setPoint(2, sf::Vector2f(buttonSize, buttonSize/2.f));
    rightButton.setPosition(WINDOW_WIDTH - buttonSize - 10.f, WINDOW_HEIGHT - buttonSize - 10.f);
    rightButton.setFillColor(sf::Color(200, 200, 200));
    

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    gameWinText.setFont(font);
    gameWinText.setString("Game Win!");
    gameWinText.setCharacterSize(30);
    gameWinText.setFillColor(sf::Color::Yellow);
    gameWinText.setPosition(
        WINDOW_WIDTH / 2 - gameWinText.getGlobalBounds().width / 2,
        WINDOW_HEIGHT / 2 - gameWinText.getGlobalBounds().height
    );

    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(
        WINDOW_WIDTH / 2 - gameOverText.getGlobalBounds().width / 2,
        WINDOW_HEIGHT / 2 - gameOverText.getGlobalBounds().height
    );

    restartText.setFont(font);
    restartText.setString("Press R to restart");
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(
        WINDOW_WIDTH / 2 - restartText.getGlobalBounds().width / 2,
        WINDOW_HEIGHT / 2 + 10
    );
}

void Game::run() {
    sf::View gameView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(gameView);

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);

        sf::Vector2f bikePos = bike.getPosition();
        gameView.setCenter(
            bikePos.x + WINDOW_WIDTH/4,  
            std::min(bikePos.y, WINDOW_HEIGHT/2.0f) 
        );
        window.setView(gameView);

        render();
    }

}



void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                reset();
            }
        }
    }

}



bool Game::checkGameOver() const {
    sf::Vector2f bikePos = bike.getPosition();
    // game over condition
    return bikePos.y > Terrain::WELL_DEPTH/2 + Terrain::BASE_HEIGHT;
}



void Game::update(float deltaTime) {
    if (!gameWon && !gameOver) {
        bike.update(deltaTime, terrain.getPoints());
        
        // check win condition
        if (bike.isFinished(terrain.getFinishX())) {
            gameWon = true;
        }
        // check game over condition
        if (checkGameOver()) {
            gameOver = true;
        }
    }

}



void Game::render() {
    window.clear(sf::Color::White);
    sf::View view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    sf::FloatRect viewBounds(
        viewCenter.x - viewSize.x/2,
        viewCenter.y - viewSize.y/2,
        viewSize.x,
        viewSize.y
    );
    
    terrain.draw(window);
    bike.draw(window);
    
    sf::View uiView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(uiView);

    window.draw(leftButton);
    window.draw(rightButton);
    
    if (gameWon) {
        window.draw(gameWinText);
        window.draw(restartText);

    } else if (gameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
    }
    window.display();

}





void Game::reset() {
    bike = Bike(100.f, 200.f);
    gameWon = false;
    gameOver = false;
} 