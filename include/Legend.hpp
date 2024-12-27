//============================================================================
// Name        : Legend.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#ifndef LEGEND_HPP
#define LEGEND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "SpaceObject.hpp"

class Legend
{
private:
    sf::Font font;               // Font to use for the text
    sf::Text text;               // Text object for rendering information
    double screenWidth, screenHeight; // Screen dimensions
    std::vector<SpaceObject *> objects; // Objects to display information about

public:
    // Constructor: Initialize the legend with parameters
    Legend(double screenWidth, double screenHeight, std::vector<SpaceObject *> objects, float x, float y);
    // Update methods
    void update(double timeStep, double totalElapsedTime, double centerX, double centerY);
    void updateObject(SpaceObject *selectedObject);

    // Render the legend to the window
    void render(sf::RenderWindow &window);

private:
    // Helper function to format a number as a string
    std::string toString(double number);
};

#endif
