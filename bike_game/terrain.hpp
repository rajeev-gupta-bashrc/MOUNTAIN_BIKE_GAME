#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Terrain {
public:
    Terrain(float amplitude, float timePeriod, float trackLength);
    void draw(sf::RenderWindow& window);
    const std::vector<sf::Vector2f>& getPoints() const;
    float getStartX() const;
    float getFinishX() const;

    static constexpr float WELL_WIDTH = 100.0f;    
    static constexpr float WELL_DEPTH = 200.0f;    
    static constexpr float BASE_HEIGHT = 300.0f;   
    static constexpr float FLAT_SECTION = 200.0f;  
private:
    std::vector<sf::Vector2f> points;
    sf::VertexArray terrain;
    sf::RectangleShape startFlag;
    sf::RectangleShape finishFlag;
    
    void generateTerrain(float amplitude, float timePeriod, float trackLength);
    void createFlags();
}; 