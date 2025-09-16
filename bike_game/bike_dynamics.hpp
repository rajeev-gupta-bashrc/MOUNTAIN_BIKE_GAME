#pragma once
#include <SFML/Graphics.hpp>

class Bike {
public:
    Bike(float startX, float startY);
    void update(float deltaTime, const std::vector<sf::Vector2f>& terrain);
    void draw(sf::RenderWindow& window);
    void handleInput();
    void reset(float startX, float startY);
    bool isFinished(float finishX) const;
    sf::Vector2f getPosition() const { return worldPosition; }

private:
    // bike parts
    sf::RectangleShape frame;
    sf::CircleShape frontWheel;
    sf::CircleShape backWheel;
    
    // wolrd frame
    sf::Vector2f worldPosition;      // x right, y down
    sf::Vector2f worldVelocity;      // how fast we're moving
    float worldRotation;             // which way we're pointing
    float worldAngularVelocity;      // how fast we're spinning
    
    // bike frame
    sf::Vector2f bikeVelocity;       // x along bike, y up/down
    float bikeRotation;              // tilt relative to ground
    float bikeAngularVelocity;       // spin speed
    
    // wheels collision
    bool frontWheelOnGround;
    bool backWheelOnGround;
    
    // physical constants
    static constexpr float GRAVITY = 500.f;        
    static constexpr float FRICTION = 0.05f;       
    static constexpr float ACCELERATION = 200.f;   
    static constexpr float MAX_SPEED = 300.f;      
    static constexpr float MASS = 1.f;           
    static constexpr float WHEEL_RADIUS = 10.f;   

    void updatePhysics(float deltaTime, const std::vector<sf::Vector2f>& terrain);
    bool checkWheelCollision(const sf::Vector2f& wheelPos, const std::vector<sf::Vector2f>& terrain);
    float getTerrainHeightAt(float x, const std::vector<sf::Vector2f>& terrain);
    void transformBikeToWorldFrame();
}; 