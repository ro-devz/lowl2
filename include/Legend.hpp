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
    sf::Font font;                      
    sf::Text text;                      
    double screenWidth, screenHeight;   
    std::vector<SpaceObject *> objects;

public:
    Legend(double screenWidth, double screenHeight, std::vector<SpaceObject *> objects, float x, float y);
    void update(double timeStep, double totalElapsedTime, double centerX, double centerY);
    void updateObject(SpaceObject *selectedObject);
    void render(sf::RenderWindow &window);
    void setObjects(std::vector<SpaceObject *> updatedObjects);

private:
    std::string toString(double number);
};

#endif
