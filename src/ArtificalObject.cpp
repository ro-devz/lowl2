//============================================================================
// Name        : ArtificialObject.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#include "ArtificialObject.hpp"
#include <iostream>
#include <string>

using namespace std;

ArtificialObject::ArtificialObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double width, double height, double thrustCapacity)
    : SpaceObject(name, x, y, vx, vy, mass, color), width(width), height(height), thrustCapacity(thrustCapacity) {}
void ArtificialObject::render(sf::RenderWindow &window, double scale, double centerX, double centerY, double ratio) const {
    double screenX = centerX + x * scale;
    double screenY = centerY + y * scale;

    // Debugging output
    cout << "Rendering " << name << " at (" << screenX << ", " << screenY << ")\n";

    double objectWidth = width / ratio;
    double objectHeight = height / ratio;

    sf::RectangleShape shape(sf::Vector2f(objectWidth, objectHeight));

    if (color == "Gray") shape.setFillColor(sf::Color(169, 169, 169));
    else if (color == "Green") shape.setFillColor(sf::Color(0, 255, 0));

    shape.setPosition(screenX - objectWidth / 2, screenY - objectHeight / 2);
    window.draw(shape);
}


bool ArtificialObject::isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const
{
    double screenX = (x - SpaceObject::getViewOffsetX()) / scale + centerX;
    double screenY = (y - SpaceObject::getViewOffsetY()) / scale + centerY;

    // Rectangle bounds
    double halfWidth = width / (2.0 * scale);
    double halfHeight = height / (2.0 * scale);

    return (mouseX >= screenX - halfWidth && mouseX <= screenX + halfWidth &&
            mouseY >= screenY - halfHeight && mouseY <= screenY + halfHeight);
}