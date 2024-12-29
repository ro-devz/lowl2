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

ArtificialObject::ArtificialObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double width, double height, double thrustCapacity, sf::Color sfColor)
    : SpaceObject(name, x, y, vx, vy, mass, color, sfColor), width(width), height(height), thrustCapacity(thrustCapacity) {}

void ArtificialObject::render(sf::RenderWindow &window, double scale, double centerX, double centerY, double ratio) const
{
    double screenX = (x - SpaceObject::getViewOffsetX()) / scale + centerX;
    double screenY = (y - SpaceObject::getViewOffsetY()) / scale + centerY;

    double baseSize = sqrt(width * height) / ratio;
    double logSize = log10(baseSize);
    double objectSize = std::max(5.0, logSize * 5.0); 

    sf::RectangleShape shape(sf::Vector2f(objectSize * 2, objectSize));

    if (color == "Gray")
        shape.setFillColor(sf::Color(169, 169, 169));
    else if (color == "Green")
        shape.setFillColor(sf::Color(0, 255, 0));
    else if (color == "White")
        shape.setFillColor(sf::Color(255, 255, 255));
    else
        shape.setFillColor(sf::Color(200, 200, 200));

    shape.setOutlineThickness(1.0f);
    shape.setOutlineColor(sf::Color::White);

    shape.setPosition(screenX - objectSize, screenY - objectSize / 2);

    if (screenX + objectSize >= 0 && screenX - objectSize <= window.getSize().x &&
        screenY + objectSize >= 0 && screenY - objectSize <= window.getSize().y)
    {
        window.draw(shape);
    }
}

bool ArtificialObject::isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const
{
    double screenX = (x - SpaceObject::getViewOffsetX()) / scale + centerX;
    double screenY = (y - SpaceObject::getViewOffsetY()) / scale + centerY;

    double baseSize = sqrt(width * height) / sizeScale;
    double logSize = log10(baseSize);
    double objectSize = std::max(5.0, logSize * 5.0);

    return (mouseX >= screenX - objectSize && mouseX <= screenX + objectSize &&
            mouseY >= screenY - objectSize/2 && mouseY <= screenY + objectSize/2);
}