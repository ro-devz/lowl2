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
    static double viewOffsetX, viewOffsetY; // Shared offsets
    string name;                            // A name
    string color;                           // A color
    double x, y;                            // A position (in m, for the center of mass, in the coordinates system)
    double vx, vy;                          // A velocity (in m/s)
    double ax, ay;                          // An acceleration (in m/s²)
    double mass;                            // A mass (in kg)
    double radius;                          // A radius (in m)
    sf::Color sfColor;                      // A color in SFML format

public:
    SpaceObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, sf::Color sfColor = sf::Color::Transparent);       
    virtual ~SpaceObject() = default;
    static void updateViewOffset(double dx, double dy);
    static double getViewOffsetX();
    static double getViewOffsetY();
    void setVelocity(double newVx, double newVy);
    const string &getName() const;
    double getX() const;
    double getY() const;
    double getMass() const;
    string getColor() const { return color; }

    void computeGravitationalForces(const vector<SpaceObject *> &objects);
    virtual void update(double timeStep);
    virtual void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxSize) const = 0;
    virtual bool isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const = 0;

    virtual void setPosition(double newX, double newY)
    {
        x = newX;
        y = newY;
    }

    virtual void adjustMass(double factor) { mass *= factor; }

    double getVx() const { return vx; }
    double getVy() const { return vy; }

    void setAcceleration(double newAx, double newAy)
    {
        ax = newAx;
        ay = newAy;
    }

    static SpaceObject *handleCollision(SpaceObject* obj1, SpaceObject* obj2);
    virtual double getCollisionRadius() const = 0;
    static sf::Color blendColors(const string& color1, const string& color2);
};

#endif
