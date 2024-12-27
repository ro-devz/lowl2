//============================================================================
// Name        : StellarObject.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
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

    // Minimum size for visibility
    double baseSize = radius / sizeScale;
    double logSize = log10(baseSize);
    double planetSize = std::max(2.0, logSize * 3.0); // Adjusted multiplier

    // Set minimum size threshold that scales with zoom
    double minSize = 2.0 / scale;
    if (planetSize < minSize)
    {
        planetSize = minSize;
    }
    sf::CircleShape shape(planetSize);

    if (color == "Yellow")
        shape.setFillColor(sf::Color(255, 255, 51)); // Bright Yellow
    else if (color == "Gray")
        shape.setFillColor(sf::Color(192, 192, 192)); // Light Gray for better contrast
    else if (color == "Red")
        shape.setFillColor(sf::Color(255, 69, 0)); // Bright Red
    else if (color == "Blue")
        shape.setFillColor(sf::Color(30, 144, 255)); // Dodger Blue for vibrancy
    else if (color == "Golden")
        shape.setFillColor(sf::Color(255, 223, 0)); // Slightly brighter Golden
    else if (color == "Light Blue")
        shape.setFillColor(sf::Color(135, 206, 250)); // Sky Blue
    else if (color == "Orange")
        shape.setFillColor(sf::Color(255, 140, 0)); // Dark Orange for brightness

    shape.setPosition(screenX - planetSize, screenY - planetSize);
    if (screenX + planetSize >= 0 && screenX - planetSize <= window.getSize().x && screenY + planetSize >= 0 && screenY - planetSize <= window.getSize().y)
    {
        window.draw(shape);
    }
}

bool StellarObject::isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const
{
    double screenX = (x - SpaceObject::getViewOffsetX()) / scale + centerX;
    double screenY = (y - SpaceObject::getViewOffsetY()) / scale + centerY;
    
    // Calculate size as in render function
    double baseSize = radius / sizeScale;
    double logSize = log10(baseSize);
    double planetSize = std::max(2.0, logSize * 3.0);  // Adjusted multiplier
    
    // Check if mouse is within planet circle
    double dx = mouseX - screenX;
    double dy = mouseY - screenY;
    return (dx * dx + dy * dy) <= (planetSize * planetSize);
}