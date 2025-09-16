#include "bike_dynamics.hpp"
#include <cmath>
#include <iostream>

Bike::Bike(float startX, float startY) {
    frame.setSize(sf::Vector2f(40.f, 20.f));
    frame.setOrigin(20.f, 10.f);
    frame.setFillColor(sf::Color::Blue);

    frontWheel.setRadius(10.f);
    frontWheel.setOrigin(10.f, 10.f);
    frontWheel.setFillColor(sf::Color::Black);

    backWheel.setRadius(10.f);
    backWheel.setOrigin(10.f, 10.f);
    backWheel.setFillColor(sf::Color::Black);

    reset(startX, startY);
}


void Bike::reset(float startX, float startY) {
    worldPosition = sf::Vector2f(startX, startY);
    worldVelocity = sf::Vector2f(0.f, 0.f);
    worldRotation = 0.f;
    worldAngularVelocity = 0.f;
    bikeVelocity = sf::Vector2f(0.f, 0.f);
    bikeRotation = 0.f;
    bikeAngularVelocity = 0.f;
    frontWheelOnGround = false;
    backWheelOnGround = false;
}



void Bike::transformBikeToWorldFrame() {
    // convert bike frame velocities to world coords
    float cosTheta = std::cos(worldRotation);
    float sinTheta = std::sin(worldRotation);
    
    worldVelocity.x = bikeVelocity.x * cosTheta - bikeVelocity.y * sinTheta;
    worldVelocity.y = bikeVelocity.x * sinTheta + bikeVelocity.y * cosTheta;
    worldAngularVelocity = bikeAngularVelocity;
}



void Bike::update(float deltaTime, const std::vector<sf::Vector2f>& terrain) {
    handleInput();
    updatePhysics(deltaTime, terrain);

    // update visuals
    frame.setPosition(worldPosition);
    frame.setRotation(worldRotation * 180.f / M_PI);
    float wheelOffset = 20.f;
    sf::Vector2f wheelDir(std::cos(worldRotation), std::sin(worldRotation));
    sf::Vector2f frontWheelPos = worldPosition + wheelDir * wheelOffset;
    sf::Vector2f backWheelPos = worldPosition - wheelDir * wheelOffset;
    frontWheel.setPosition(frontWheelPos);
    backWheel.setPosition(backWheelPos);
}



void Bike::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        bikeVelocity.x = std::min(bikeVelocity.x + ACCELERATION * 0.016f, MAX_SPEED);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        bikeVelocity.x = std::max(bikeVelocity.x - ACCELERATION * 0.016f, -MAX_SPEED);
    }
    
}




void Bike::updatePhysics(float deltaTime, const std::vector<sf::Vector2f>& terrain) {
    float wheelOffset = 20.f;
    sf::Vector2f wheelDir(std::cos(worldRotation), std::sin(worldRotation));
    sf::Vector2f frontWheelPos = worldPosition + wheelDir * wheelOffset;
    sf::Vector2f backWheelPos = worldPosition - wheelDir * wheelOffset;

    frontWheelOnGround = checkWheelCollision(frontWheelPos, terrain);
    backWheelOnGround = checkWheelCollision(backWheelPos, terrain);

    // physics in bike frame
    if (!frontWheelOnGround && !backWheelOnGround) {
        bikeVelocity.y += GRAVITY * deltaTime;
    }
    else {
        bikeVelocity.y = 0.f;  // stop falling
        
        float terrainAngle = std::atan2(
            getTerrainHeightAt(worldPosition.x + 1, terrain) - getTerrainHeightAt(worldPosition.x, terrain),
            1.0f
        );

        float gravityForceX = GRAVITY * std::sin(terrainAngle);
        bikeVelocity.x += gravityForceX * deltaTime;

        float gravityForceY = GRAVITY * std::cos(terrainAngle);
        float frictionForce = FRICTION * MASS * gravityForceY * (bikeVelocity.x > 0 ? -1 : 1);
        bikeVelocity.x += frictionForce * deltaTime;
    }

    transformBikeToWorldFrame();
    worldPosition += worldVelocity * deltaTime;

    // check if the bike is going below the ground
    float CurrentTerrainHeight = getTerrainHeightAt(worldPosition.x, terrain);
    if (worldPosition.y > CurrentTerrainHeight - WHEEL_RADIUS) {
        worldPosition.y = CurrentTerrainHeight - WHEEL_RADIUS;
    }

    // set bike rotation to the ground slope if on ground
    if (frontWheelOnGround || backWheelOnGround) {
        float targetRotation = std::atan2(
            getTerrainHeightAt(worldPosition.x + 1, terrain) - getTerrainHeightAt(worldPosition.x, terrain),
            1.0f
        );
        worldRotation = targetRotation;
        bikeRotation = 0.f;  // reset bike tilt
    }

}

bool Bike::checkWheelCollision(const sf::Vector2f& wheelPos, const std::vector<sf::Vector2f>& terrain) {
    float terrainHeight = getTerrainHeightAt(wheelPos.x, terrain);
    return wheelPos.y >= terrainHeight - 10.f; //wheel radius is 10.f
}



float Bike::getTerrainHeightAt(float x, const std::vector<sf::Vector2f>& terrain) {
    if (int(x) >= terrain.size()) {
        return terrain.back().y;
    }
    return terrain[int(x)].y;
}




void Bike::draw(sf::RenderWindow& window) {
    window.draw(frame);
    window.draw(frontWheel);
    window.draw(backWheel);
}
bool Bike::isFinished(float finishX) const {
    return worldPosition.x >= finishX;
} 


