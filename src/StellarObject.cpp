#include "StellarObject.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

// Constructor implementation
StellarObject::StellarObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double radius)
    : SpaceObject(name, x, y, vx, vy, mass, color), radius(radius) {}

void StellarObject::render(sf::RenderWindow &window, double scale, double centerX, double centerY, double sizeScale) const
{
    // Scale positions with the zoom factor
    double screenX = centerX + (x / scale); // Distance scaling
    double screenY = centerY + (y / scale); // Distance scaling
    double planetSize = radius / sizeScale; // Size scaling

    // Minimum size for visibility
    if (planetSize < 2.0)
        planetSize = 2.0;
    if (planetSize < 1.0)
        planetSize = 1.0;
    // Create circle shape
    sf::CircleShape shape(planetSize);

    // Set the color of the shape based on the color string
    if (color == "Yellow")
        shape.setFillColor(sf::Color::Yellow);
    else if (color == "Gray")
        shape.setFillColor(sf::Color(169, 169, 169)); // Gray color
    else if (color == "Red")
        shape.setFillColor(sf::Color::Red);
    else if (color == "Blue")
        shape.setFillColor(sf::Color::Blue);
    else if (color == "Golden")
        shape.setFillColor(sf::Color(255, 215, 0)); // Golden color
    else if (color == "Light Blue")
        shape.setFillColor(sf::Color(173, 216, 230)); // Light Blue
    else if (color == "Orange")
        shape.setFillColor(sf::Color(255, 165, 0)); // Orange color

    // Check if object is offscreen
    if (screenX < 0 || screenX > window.getSize().x || screenY < 0 || screenY > window.getSize().y)
    {
        std::cout << "Warning: Object " << name << " is offscreen!" << std::endl;
    }

    // Set the position of the circle shape (center it on the screen)
    shape.setPosition(screenX - planetSize / 2, screenY - planetSize / 2);

    // Draw the shape to the window
    window.draw(shape);
}