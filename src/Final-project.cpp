#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "ArtificialObject.hpp"
#include "StellarObject.hpp"
#include <SFML/Graphics.hpp>
#include "Legend.hpp" // Include the legend header

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Proportional Star System Simulation");
    window.setFramerateLimit(60);

    // Constants
    const double timeStep = 86400.0; // 1 day per simulation second (in seconds)
    const double G = 6.67430e-11;    // Gravitational constant

    // Scaling factors
    const double SCREEN_WIDTH = 1200.0;
    const double SCREEN_HEIGHT = 800.0;

    // Maximum distance (from the Sun to Neptune) and radius (Sun's radius)
    const double MAX_DISTANCE = 4.49825e12; // Neptune's distance (meters)
    const double MAX_RADIUS = 696340.0e3;   // Sun's radius (meters)

    // Define the scaling ratios:
    const double DISTANCE_SCALE_RATIO = 5.0; // Distance ratio (5 meters in real life = 1 pixel on screen)
    const double SIZE_SCALE_RATIO = 10.0;    // Size ratio (planet size in real life = 10 times smaller)

    // Calculate scaling factors based on the ratios
    const double SCALE = MAX_DISTANCE / (SCREEN_WIDTH * DISTANCE_SCALE_RATIO); // 1 pixel = X meters
    const double SIZE_SCALE = MAX_RADIUS / SIZE_SCALE_RATIO;                   // 1 km = X pixels for planet sizes

    // Center of the screen
    const double centerX = SCREEN_WIDTH / 2;
    const double centerY = SCREEN_HEIGHT / 2;

    // Sun (reference point at the origin)
    StellarObject sun("Sun", 0, 0, 0, 0, 1.989e30, "Yellow", 696340.0e3); // Radius: 696,340 km

    // Define planets with data from Wikipedia
    StellarObject mercury("Mercury", 57.91e9, 0, 0, 47.872e3, 3.3011e23, "Gray", 4879.0e3);
    StellarObject venus("Venus", 108.2e9, 0, 0, 35.02e3, 4.8675e24, "Yellow", 12104.0e3);
    StellarObject earth("Earth", 149.6e9, 0, 0, 29.783e3, 5.9724e24, "Blue", 12742.0e3);
    StellarObject mars("Mars", 227.94e9, 0, 0, 24.077e3, 6.4171e23, "Red", 6779.0e3);
    StellarObject jupiter("Jupiter", 778.5e9, 0, 0, 13.07e3, 1.8982e27, "Orange", 139820.0e3);
    StellarObject saturn("Saturn", 1.4294e12, 0, 0, 9.687e3, 5.6834e26, "Gold", 116460.0e3);
    StellarObject uranus("Uranus", 2.87099e12, 0, 0, 6.81e3, 8.6810e25, "LightBlue", 50724.0e3);
    StellarObject neptune("Neptune", 4.49825e12, 0, 0, 5.43e3, 1.02413e26, "Blue", 49244.0e3);
    StellarObject moon("Moon", 384400.0e3, 0, 0, 1.022e3, 7.342e22, "Gray", 1737.4e3);

    // Set Earth as the parent of the Moon
   // moon.setParent(&earth);

    // List of objects
    vector<SpaceObject *> objects = {&sun, &mercury, &venus, &earth, &mars, &jupiter, &saturn, &uranus, &neptune};

    Legend legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects);
    double totalElapsedTime = 0.0;

     bool isMouseDragging = false;
    sf::Vector2i lastMousePos;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Handle mouse movement
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Middle) {
                    isMouseDragging = true;
                    lastMousePos = sf::Mouse::getPosition(window);
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Middle) {
                    isMouseDragging = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved && isMouseDragging) {
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = currentMousePos - lastMousePos;
                
                // Convert screen movement to world coordinates
                double worldDeltaX = delta.x * SCALE;
                double worldDeltaY = delta.y * SCALE;
                
                // Update the view offset
                SpaceObject::updateViewOffset(worldDeltaX, worldDeltaY);
                lastMousePos = currentMousePos;
            }
        }

        // Update simulation
        for (auto *obj : objects) {
            obj->computeGravitationalForces(objects);
            obj->update(timeStep);
        }

        // Clear and render
        window.clear(sf::Color::Black);
        for (auto *obj : objects) {
            obj->render(window, SCALE, window.getSize().x / 2.0, window.getSize().y / 2.0, SIZE_SCALE);
        }

        // Update and render legend with correct coordinates
        totalElapsedTime += timeStep;
        legend.update(timeStep, totalElapsedTime, SpaceObject::getViewOffsetX(), SpaceObject::getViewOffsetY());
        legend.render(window);

        window.display();
    }

    return 0;
}