//============================================================================
// Name        : Simulation.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#include "Simulation.hpp"
#include "StellarObject.hpp"
#include "ArtificialObject.hpp"
#include <cmath>
#include "Legend.hpp"

Simulation::Simulation()
    : window(sf::VideoMode(1200, 800), "Proportional Star System Simulation"),
      realTimeStep(86000.0),
      totalElapsedTime(0.0),
      viewScale(1.0),
      isMouseDragging(false),
      isDraggingObject(false),
      selectedObject(nullptr),
      isObjectSelected(false),
      SCREEN_WIDTH(1200.0),
      SCREEN_HEIGHT(800.0),
      MAX_DISTANCE(4.49825e12),
      MAX_RADIUS(696340.0e3),
      DISTANCE_SCALE_RATIO(10.0),
      SIZE_SCALE_RATIO(20000.0),
      SCALE(MAX_DISTANCE / (SCREEN_WIDTH * DISTANCE_SCALE_RATIO)),
      SIZE_SCALE(MAX_RADIUS / SIZE_SCALE_RATIO)
{
    window.setFramerateLimit(60);
    initializeObjects();
}

void Simulation::initializeObjects()
{
    // Sun
    StellarObject *sun = new StellarObject("Sun", 0, 0, 0, 0, 1.989e30, "Yellow", 696340.0e3);

    // Planets
    StellarObject *mercury = new StellarObject("Mercury", 57.91e9, 0, 0, 47.872e3, 3.3011e23, "Gray", 4879.0e3);
    StellarObject *venus = new StellarObject("Venus", 108.2e9, 0, 0, 35.02e3, 4.8675e24, "Yellow", 12104.0e3);
    StellarObject *earth = new StellarObject("Earth", 149.6e9, 0, 0, 29.783e3, 5.9724e24, "Blue", 12742.0e3);
    StellarObject *mars = new StellarObject("Mars", 227.94e9, 0, 0, 24.077e3, 6.4171e23, "Red", 6779.0e3);
    StellarObject *jupiter = new StellarObject("Jupiter", 778.5e9, 0, 0, 13.07e3, 1.8982e27, "Orange", 139820.0e3);
    StellarObject *saturn = new StellarObject("Saturn", 1.4294e12, 0, 0, 9.687e3, 5.6834e26, "Gold", 116460.0e3);
    StellarObject *uranus = new StellarObject("Uranus", 2.87099e12, 0, 0, 6.81e3, 8.6810e25, "LightBlue", 50724.0e3);
    StellarObject *neptune = new StellarObject("Neptune", 4.49825e12, 0, 0, 5.43e3, 1.02413e26, "Blue", 49244.0e3);

    // Moons
    double moonOrbitSpeed = sqrt((6.67430e-11 * earth->getMass()) / 384400.0e3);
    StellarObject *moon = new StellarObject("Moon",
                                            earth->getX() + 384400.0e3,
                                            earth->getY(),
                                            0,
                                            29.783e3 + moonOrbitSpeed,
                                            7.342e22, "Gray", 1737.4e3);

    double europaOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 0.671e9);
    StellarObject *europa = new StellarObject("Europa",
                                              jupiter->getX() + 0.671e9,
                                              jupiter->getY(),
                                              0,
                                              13.07e3 + europaOrbitSpeed,
                                              4.7998e22, "White", 1560.8e3);

    double ioOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 0.422e9);
    StellarObject *io = new StellarObject("Io",
                                          jupiter->getX() + 0.422e9,
                                          jupiter->getY(),
                                          0,
                                          13.07e3 + ioOrbitSpeed,
                                          8.9319e22, "Yellow", 1821.6e3);

    double ganymedeOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 1.07e9);
    StellarObject *ganymede = new StellarObject("Ganymede",
                                       jupiter->getX() + 1.07e9,
                                       jupiter->getY(),
                                       0,
                                       13.07e3 + ganymedeOrbitSpeed,
                                       1.4819e23, "Gray", 2634.1e3);

    // Callisto (Jupiter's moon)
    double callistoOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 1.883e9);
    StellarObject *callisto = new StellarObject("Callisto",
                                       jupiter->getX() + 1.883e9,
                                       jupiter->getY(),
                                       0,
                                       13.07e3 + callistoOrbitSpeed,
                                       1.0759e23, "Gray", 2410.3e3);

    // Titan (Saturn's moon)
    double titanOrbitSpeed = sqrt((6.67430e-11 * saturn->getMass()) / 1.22e9);
    StellarObject *titan = new StellarObject("Titan",
                                    saturn->getX() + 1.22e9,
                                    saturn->getY(),
                                    0,
                                    9.687e3 + titanOrbitSpeed,
                                    1.3452e23, "Yellow", 2574.7e3);

    ArtificialObject *iss = new ArtificialObject("ISS",
                                     earth->getX() + 408e5,
                                     earth->getY(),
                                     0,
                                     29.783e3 + 7.66e3,
                                     419725,
                                     "Gray",
                                     108.5,
                                     51.6,
                                     4e4);

    // Hubble Space Telescope
    ArtificialObject *hubble = new ArtificialObject("Hubble",
                                        earth->getX() + 540e3,
                                        earth->getY(),
                                        0,
                                        29.783e3 + 7.5e3,
                                        11110,
                                        "Green",
                                        13.2,
                                        4.2,
                                        2e4);

    // GPS satellite
    ArtificialObject *gps = new ArtificialObject("GPS",
                                     earth->getX() + 20200e3,
                                     earth->getY(),
                                     0,
                                     29.783e3 + 3.87e3,
                                     1630,
                                     "Green",
                                     5.3,
                                     2.7,
                                     1e4);

    objects = {sun, earth, moon, europa, io, mercury, venus, mars, jupiter, saturn, uranus, neptune};
    objects.push_back(ganymede);
    objects.push_back(callisto);
    objects.push_back(titan);
    objects.push_back(iss);
}

void Simulation::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && selectedObject)
            {
                isDraggingObject = true;
                dragStartPos = sf::Mouse::getPosition(window);
            }

            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                isMouseDragging = true;
                lastMousePos = sf::Mouse::getPosition(window);
            }

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                double mouseX = event.mouseButton.x;
                double mouseY = event.mouseButton.y;

                SpaceObject *clickedObject = nullptr;
                for (auto *obj : objects)
                {
                    if (obj->isClicked(mouseX, mouseY, SCALE / viewScale,
                                       window.getSize().x / 2.0, window.getSize().y / 2.0, SIZE_SCALE))
                    {
                        clickedObject = obj;
                        break;
                    }
                }

                if (clickedObject && !isObjectSelected)
                {
                    selectedObject = clickedObject;
                    isObjectSelected = true;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                isDraggingObject = false;

            if (event.mouseButton.button == sf::Mouse::Middle)
                isMouseDragging = false;
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
        else if (event.type == sf::Event::MouseMoved && isDraggingObject && selectedObject)
        {
            sf::Vector2i currentPos = sf::Mouse::getPosition(window);
            sf::Vector2i delta = currentPos - dragStartPos;

            // Convert screen coordinates to world coordinates
            double worldDeltaX = delta.x * SCALE / viewScale;
            double worldDeltaY = delta.y * SCALE / viewScale;

            selectedObject->setPosition(
                selectedObject->getX() + worldDeltaX,
                selectedObject->getY() + worldDeltaY);

            dragStartPos = currentPos;
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta > 0)
                viewScale *= 1.1;
            else
                viewScale *= 0.9;

            viewScale = std::max(0.0001, std::min(viewScale, 100.0));
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (selectedObject)
            {
                if (event.key.code == sf::Keyboard::Delete)
                {
                    objects.erase(
                        std::remove(objects.begin(), objects.end(), selectedObject),
                        objects.end());
                    selectedObject = nullptr;
                    isObjectSelected = false;
                    break;
                }

                if (event.key.code == sf::Keyboard::Add)
                    selectedObject->adjustMass(1.1);

                if (event.key.code == sf::Keyboard::Subtract)
                    selectedObject->adjustMass(0.9);
                if (event.key.code == sf::Keyboard::Escape)
                {
                    selectedObject = nullptr;
                    isObjectSelected = false;
                }
            }
            if (!selectedObject)
            {
                if (event.key.code == sf::Keyboard::Add)
                    realTimeStep += 3600.f;
                if (event.key.code == sf::Keyboard::Subtract)
                    realTimeStep -= 3600.f;
                if (event.key.code == sf::Keyboard::Multiply)
                    SpaceObject::updateViewOffset(-SpaceObject::getViewOffsetX(), -SpaceObject::getViewOffsetY());
            }
        }
    }
}
void Simulation::update(float deltaTime, Legend *legend, Legend *infoMenu)
{
    double adjustedTimeStep = realTimeStep * deltaTime;

    bool collisionOccurred = false;
    SpaceObject *obj1 = nullptr;
    SpaceObject *obj2 = nullptr;

    // First, detect if any collision occurs
    for (size_t i = 0; i < objects.size() && !collisionOccurred; i++)
    {
        for (size_t j = i + 1; j < objects.size() && !collisionOccurred; j++)
        {
            double dx = objects[i]->getX() - objects[j]->getX();
            double dy = objects[i]->getY() - objects[j]->getY();
            double distance = sqrt(dx * dx + dy * dy);

            if (distance < (objects[i]->getCollisionRadius() + objects[j]->getCollisionRadius()))
            {
                collisionOccurred = true;
                obj1 = objects[i]; // This correctly stores the pointer to the object
                obj2 = objects[j]; // This correctly stores the pointer to the other object
            }
        }
    }

    // Handle the collision if one occurred
    if (collisionOccurred)
    {
        SpaceObject *newObject = SpaceObject::handleCollision(obj1, obj2);

        // If the selected object is one of the colliding objects, update it to the new object
        if (selectedObject == obj1 || selectedObject == obj2)
        {
            selectedObject = newObject;
        }

        // Remove obj1 and obj2 from the vector, ensure safe removal
        objects.erase(std::remove(objects.begin(), objects.end(), obj1), objects.end());
        objects.erase(std::remove(objects.begin(), objects.end(), obj2), objects.end());

        // Delete the old objects to prevent memory leaks
        delete obj1;
        delete obj2;

        // Add the new object created after the collision
        objects.push_back(newObject);
        legend->setObjects(objects);
        infoMenu->setObjects(objects);
    }

    // Continue with regular update
    for (SpaceObject *obj : objects)
    {
        obj->computeGravitationalForces(objects);
    }

    totalElapsedTime += adjustedTimeStep;
    legend->update(realTimeStep, totalElapsedTime, SpaceObject::getViewOffsetX(), SpaceObject::getViewOffsetY());

    for (SpaceObject *obj : objects)
    {
        obj->update(adjustedTimeStep);
    }
}
void Simulation::render(Legend *legend, Legend *infoMenu)
{
    window.clear(sf::Color::Black);

    // Render all objects
    for (auto *obj : objects)
    {
        obj->render(window, SCALE / viewScale, window.getSize().x / 2.0,
                    window.getSize().y / 2.0, SIZE_SCALE);
    }

    legend->render(window);
    infoMenu->updateObject(selectedObject);
    infoMenu->render(window);
    window.display();
}

void Simulation::run()
{
    sf::Clock clock;

    Legend *legend = new Legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects, 10.f, 10.f);
    Legend *infoMenu = new Legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects, SCREEN_WIDTH - 300.f, 10.f);

    while (window.isOpen())
    {
        handleEvents();
        update(clock.restart().asSeconds(), legend, infoMenu);
        render(legend, infoMenu);
    }

    // Cleanup
    for (auto *obj : objects)
    {
        delete obj;
    }
    delete legend; // Clean up the dynamically allocated memory
    delete infoMenu;
}