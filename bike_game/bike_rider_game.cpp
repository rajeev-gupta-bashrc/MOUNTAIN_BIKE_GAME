/*

2D Bike Rider Game – Game Specification Prompt
A 2D side-scrolling physics-based bike game using C++ and SFML with the following features:
 Game Environment:
* Screen size: 500x400 pixels.
* Terrain: a simple sine wave with some random and small square wells symmetrically placed about the peak of the sine wave.
* Start/Finish indicators: Visible flags at beginning and end of the terrain.
 Player Mechanics:
* Bike: A simple rectangle with two circular wheels in front and back.
* Controls:
   * Right arrow / On-screen right button: Accelerate.
   * Left arrow / On-screen left button: Brake/reverse.
* Physics:
   * world frame: top left corner of the window, x : horizontally left to right, y: vertically downwards
   * bike frame: center of the left wheel; x: parallel to the ground left to right, y: perpendicular to the ground downwards
   * Gravity:
        * if bike on ground:
            get gravity component in the x direction of the bike frame, accelerate bike frame in the x direction;
        * if bike not on ground:
            get gravity component in the y direction of the bike frame, accelerate bike frame in the y direction;
   * friction: two variables to track if both wheels are on ground or not.
        * if a wheel is on ground:
            get friction component in the x direction of the bike frame, accelerate bike frame in the x direction
   * collision detection:
        if bike touches the ground, set y velocity of bike frame to 0.
   * if right/left arrow is pressed, then accelerate bike frame towards its positive/negative x direction.
   * use translational and rotational kinematics to calculate the final velocity and angular velocity of the bike frame.
 UI/UX:
* Two on-screen buttons at bottom corners for mobile-like controls.
* Text pop-up for:
   * Game Win (player reaches end)
   * Press R to restart
 Dependencies:
* SFML (Simple and Fast Multimedia Library) for graphics and input
* No external physics engine (custom implementation for educational clarity)


*/

#include "game_ui.hpp"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

