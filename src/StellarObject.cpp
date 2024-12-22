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
    double screenX = (x - SpaceObject::getViewOffsetX()) / scale + window.getSize().x / 2.0;
    double screenY = (y - SpaceObject::getViewOffsetY()) / scale + window.getSize().y / 2.0;
    double planetSize = std::max(2.0, radius / sizeScale);
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

    shape.setPosition(screenX - planetSize, screenY - planetSize);
    if (screenX + planetSize >= 0 && screenX - planetSize <= window.getSize().x && screenY + planetSize >= 0 && screenY - planetSize <= window.getSize().y)
    {
        window.draw(shape);
    }
}
