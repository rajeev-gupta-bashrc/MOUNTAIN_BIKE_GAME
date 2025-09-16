#include "terrain.hpp"
#include <cmath>
#include <vector>

Terrain::Terrain(float amplitude, float timePeriod, float trackLength) : terrain(sf::LineStrip) {
    generateTerrain(amplitude, timePeriod, trackLength);
    createFlags();
}

void Terrain::draw(sf::RenderWindow& window) {
    window.draw(terrain);
    window.draw(startFlag);
    window.draw(finishFlag);
}

const std::vector<sf::Vector2f>& Terrain::getPoints() const {
    return points;
}



float Terrain::getStartX() const {
    return points[0].x;
}

float Terrain::getFinishX() const {
    return points.back().x;
} 



void Terrain::generateTerrain(float amplitude, float timePeriod, float trackLength) {
    const int numPoints = static_cast<int>(trackLength);  // one point per pixel
    const float dx = 1.0f;  // space between points
    const float frequency = 2 * M_PI / timePeriod;
    
    points.clear();
    terrain.clear();

    // make flat area

    for (int i = 0; i < static_cast<int>(FLAT_SECTION); ++i) {
        float x = i * dx;
        float y = BASE_HEIGHT;
        points.push_back(sf::Vector2f(x, y));
    }

    // make wavy part

    for (int i = static_cast<int>(FLAT_SECTION); i < numPoints; ++i) {
        float x = i * dx;
        float sineValue = std::sin(frequency * (x - FLAT_SECTION));  // start waves after flat bit
        float y = BASE_HEIGHT + amplitude * sineValue;
        points.push_back(sf::Vector2f(x, y));
    }

    // find first dip
    int firstMinIndex = -1;
    for (int i = static_cast<int>(FLAT_SECTION) + 1; i < numPoints - 1; ++i) {  // look after flat part
        if (points[i].y < points[i-1].y && points[i].y < points[i+1].y) {
            firstMinIndex = i;
            break;
        }
    }

    // put wells at low points

    if (firstMinIndex != -1) {
        int halfWellWidth = static_cast<int>(WELL_WIDTH / 2);
        float period = timePeriod; 
        for (int minIndex = firstMinIndex; minIndex < numPoints - halfWellWidth; minIndex += static_cast<int>(period)) {
            if (minIndex - halfWellWidth >= 0 && minIndex + halfWellWidth < numPoints) {
                for (int j = minIndex - halfWellWidth; j <= minIndex + halfWellWidth; ++j) {
                    points[j].y = BASE_HEIGHT + WELL_DEPTH;
                }
            }
        }
    }

    // draw the terrain
    for (const auto& point : points) {
        terrain.append(sf::Vertex(point, sf::Color::Green));
    }

}



void Terrain::createFlags() {
    // start flag
    startFlag.setSize(sf::Vector2f(5.f, 30.f));
    startFlag.setPosition(200.f, points[200].y - 30.f);
    startFlag.setFillColor(sf::Color::Green);

    // finish flag
    finishFlag.setSize(sf::Vector2f(5.f, 30.f));
    finishFlag.setPosition(points.back().x, points.back().y - 30.f);
    finishFlag.setFillColor(sf::Color::Red);
}