//============================================================================
// Name        : Simulation.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "SpaceObject.hpp"
#include "Legend.hpp"

class Simulation {
private:
    sf::RenderWindow window;
    std::vector<SpaceObject*> objects;
    double realTimeStep;
    double totalElapsedTime;
    double viewScale;
    bool isMouseDragging;
    bool isDraggingObject;
    sf::Vector2i lastMousePos;
    sf::Vector2i dragStartPos;
    SpaceObject* selectedObject;
    bool isObjectSelected;
    
    // Constants
    const double SCREEN_WIDTH;
    const double SCREEN_HEIGHT;
    const double MAX_DISTANCE;
    const double MAX_RADIUS;
    const double DISTANCE_SCALE_RATIO;
    const double SIZE_SCALE_RATIO;
    const double SCALE;
    const double SIZE_SCALE;

    void handleEvents();
    void update(float deltaTime, Legend *legend, Legend *infoMenu);
    void render(Legend *legend, Legend *infoMenu);
    void initializeObjects();

public:
    Simulation();
    void run();
};

#endif
