//============================================================================
// Name        : SpaceObject.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#ifndef SPACE_OBJECT_HPP
#define SPACE_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class SpaceObject
{
protected:
    string name;  // A name
    string color; // A color
    double x, y;   // A position (in m, for the center of mass, in the coordinates system)
    double vx, vy; // A velocity (in m/s)
    double ax, ay; // An acceleration (in m/s²)
    double mass;   // A mass (in kg)
    double radius; // A radius (in m)

public:
    SpaceObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color)
        : name(name), color(color), x(x), y(y), vx(vx), vy(vy), ax(0), ay(0), mass(mass), radius(0) {}

    virtual ~SpaceObject() = default;

    const string &getName() const { return name; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getMass() const { return mass; }

    void computeGravitationalForces(const vector<SpaceObject *> &objects)
    {
        const double G = 6.67430e-11;      // Gravitational constant
        const double MIN_DISTANCE = 1.0e4; // Minimum distance (10 km)
        ax = ay = 0;                      // Reset acceleration

        cout << "\n--- Compute Gravitational Forces ---\n";
        cout << "Object: " << name << "\n";

        for (const auto *obj : objects)
        {
            if (obj == this)
                continue;

            // Vector from this object to the other object
            double dx = obj->getX() - x; 
            double dy = obj->getY() - y;
            double distanceSq = dx * dx + dy * dy;

            // Cap minimum distance to avoid singularities
            if (distanceSq < MIN_DISTANCE * MIN_DISTANCE)
            {
                distanceSq = MIN_DISTANCE * MIN_DISTANCE;
            }

            double distance = sqrt(distanceSq);

            // Calculate acceleration directly to avoid numerical overflow
            // Using Newton's law: a = GM/r^2 * (unit vector)
            double accelMagnitude = G * obj->getMass() / distanceSq;

            // Normalize direction vector
            double unitX = dx / distance;
            double unitY = dy / distance;

            // Calculate acceleration components
            ax += static_cast<double>(accelMagnitude * unitX);
            ay += static_cast<double>(accelMagnitude * unitY);

            cout << "Interacting with: " << obj->getName() << "\n";
            cout << "Distance: " << distance << "m\n";
            cout << "Acceleration magnitude: " << accelMagnitude << "m/s^2\n";
            cout << "Direction - unitX: " << unitX << " unitY: " << unitY << "\n";
            cout << "Current acceleration - ax: " << ax << " ay: " << ay << "\n";
        }

        cout << "Final Acceleration - ax: " << ax << " ay: " << ay << "\n";
    }

    virtual void update(double timeStep)
    {
        // Update velocity
        vx += ax * timeStep;
        vy += ay * timeStep;
        cout << vx << vy << "Vitesse of the planet" << name << endl;

        // Update position
        x += vx * timeStep;
        y += vy * timeStep;
        cout << x << y << "   Position of the planet" << name << endl;
    }

    virtual void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxSize) const = 0;
};

#endif
