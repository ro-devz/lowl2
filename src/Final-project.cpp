#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <windows.h>
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
    double realTimeStep = 86000.0; // 1 hour in simulation (real time step)

    // Scaling factors
    const double SCREEN_WIDTH = 1200.0;
    const double SCREEN_HEIGHT = 800.0;
    const double MAX_DISTANCE = 4.49825e12;                                    // Neptune's distance
    const double MAX_RADIUS = 696340.0e3;                                      // Sun's radius
    const double DISTANCE_SCALE_RATIO = 10.0;                                  // Distance ratio
    const double SIZE_SCALE_RATIO = 2000.0;                                    // Size ratio
    const double SCALE = MAX_DISTANCE / (SCREEN_WIDTH * DISTANCE_SCALE_RATIO); // 1 pixel = X meters
    const double SIZE_SCALE = MAX_RADIUS / SIZE_SCALE_RATIO;                   // 1 km = X pixels for planet sizes

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
    StellarObject europa("Europa", 0.671e9, 0, 0, 1.0e3, 4.7998e22, "White", 1560.8e3);
    StellarObject io("Io", 0.422e9, 0, 0, 1.8e3, 8.9319e22, "Yellow", 1821.6e3);

    // List of objects
    vector<SpaceObject *> objects = {&sun, &earth, &moon, &europa, &io, &mercury, &venus, &mars, &jupiter, &saturn, &uranus, &neptune};

    Legend legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects, 10.f, 10.f);
    Legend infoMenu(SCREEN_WIDTH, SCREEN_HEIGHT, objects, SCREEN_WIDTH - 300.f, 10.f);
    double totalElapsedTime = 0.0;

    // Use sf::Clock to measure elapsed time
    sf::Clock clock;

    bool isMouseDragging = false;
    sf::Vector2i lastMousePos;
    double viewScale = 1.0; // Add zoom factor
    SpaceObject *selectedObject = nullptr;
    bool isObjectSelected = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    isMouseDragging = true;
                    lastMousePos = sf::Mouse::getPosition(window);
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    double mouseX = event.mouseButton.x;
                    double mouseY = event.mouseButton.y;

                    // Check if the user clicked on an object
                    SpaceObject *clickedObject = nullptr;
                    for (auto *obj : objects)
                    {
                        if (obj->isClicked(mouseX, mouseY, SCALE / viewScale, window.getSize().x / 2.0, window.getSize().y / 2.0, SIZE_SCALE))
                        {
                            clickedObject = obj;
                            break;
                        }
                    }

                    if (clickedObject && !isObjectSelected) // Only update if no object is selected
                    {
                        selectedObject = clickedObject;
                        isObjectSelected = true; // Mark the object as selected
                    }
                    else if (!clickedObject) // Deselect if clicking outside any object
                    {
                        selectedObject = nullptr;
                        isObjectSelected = false; // Reset selection flag
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    isMouseDragging = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved && isMouseDragging)
            {
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = currentMousePos - lastMousePos;

                double worldDeltaX = -delta.x * SCALE / viewScale;
                double worldDeltaY = -delta.y * SCALE / viewScale;

                SpaceObject::updateViewOffset(worldDeltaX, worldDeltaY);
                lastMousePos = currentMousePos;
            }
            // Add mouse wheel zoom
            else if (event.type == sf::Event::MouseWheelScrolled)
            {

                if (event.mouseWheelScroll.delta > 0)
                    viewScale *= 1.1; // Zoom in
                else
                    viewScale *= 0.9; // Zoom out

                // Clamp zoom levels
                viewScale = std::max(0.01, std::min(viewScale, 10.0));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (!selectedObject)
                {
                    if (event.key.code == sf::Keyboard::Add)
                        realTimeStep += 3600.f;
                    if (event.key.code == sf::Keyboard::Subtract)
                        realTimeStep -= 3600.f;
                    if (event.key.code == sf::Keyboard::Multiply)
                        SpaceObject::updateViewOffset(-SpaceObject::getViewOffsetX(), -SpaceObject::getViewOffsetY()); // Reset to center the Sun
                }
            }
        }

        // Measure elapsed time since last frame
        float deltaTime = clock.restart().asSeconds();

        // Adjust the time step for smoother movement
        double adjustedTimeStep = realTimeStep * deltaTime;

        // Update simulation
        for (auto *obj : objects)
            obj->computeGravitationalForces(objects);

        window.clear(sf::Color::Black);

        // Update simulation based on the adjusted time step
        totalElapsedTime += adjustedTimeStep;

        legend.update(realTimeStep, totalElapsedTime, SpaceObject::getViewOffsetX(), SpaceObject::getViewOffsetY());

        for (auto *obj : objects)
        {
            obj->update(adjustedTimeStep);
            obj->render(window, SCALE / viewScale, window.getSize().x / 2.0, window.getSize().y / 2.0, SIZE_SCALE);
        }

        legend.render(window);
        infoMenu.updateObject(selectedObject);
        infoMenu.render(window);
        window.display();
    }

    return 0;
}
