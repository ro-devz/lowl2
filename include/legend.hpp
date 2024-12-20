#ifndef LEGEND_HPP
#define LEGEND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "SpaceObject.hpp"

class Legend
{
private:
    sf::Font font;      // Font to use for the text
    sf::Text text;      // Text object for rendering information
    double screenWidth, screenHeight;
    std::vector<SpaceObject*> objects;

public:
    // Constructor
    Legend(double screenWidth, double screenHeight, std::vector<SpaceObject*> objects);

    // Update method to update time and object information
    void update(double timeStep, double totalElapsedTime, double centerX, double centerY);

    // Render method to draw the legend to the window
    void render(sf::RenderWindow &window);

private:
    // Helper function to convert a number to string
    std::string toString(double number);
};

#endif
