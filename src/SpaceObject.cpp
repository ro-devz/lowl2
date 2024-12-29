//============================================================================
// Name        : SpaceObject.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#include "SpaceObject.hpp"
#include "StellarObject.hpp"

double SpaceObject::viewOffsetX = 0.0;
double SpaceObject::viewOffsetY = 0.0;

SpaceObject::SpaceObject(const string &name, double x, double y, double vx,
                         double vy, double mass, const string &color, sf::Color sfColor)
    : name(name), color(color), x(x), y(y), vx(vx), vy(vy), ax(0), ay(0),
      mass(mass), sfColor(sfColor == sf::Color::Transparent ? sf::Color::Transparent : sfColor), radius(0) {}


void SpaceObject::updateViewOffset(double dx, double dy)
{
    viewOffsetX += dx;
    viewOffsetY += dy;
}

double SpaceObject::getViewOffsetX() { return viewOffsetX; }
double SpaceObject::getViewOffsetY() { return viewOffsetY; }
const string &SpaceObject::getName() const { return name; }
double SpaceObject::getX() const { return x; }
double SpaceObject::getY() const { return y; }
double SpaceObject::getMass() const { return mass; }

void SpaceObject::computeGravitationalForces(const vector<SpaceObject *> &objects)
{
    const double G = 6.67430e-11, MIN_DISTANCE = 1.0e4;
    ax = ay = 0;

    for (const auto *obj : objects)
    {
        if (obj == this)
            continue;

        double dx = obj->getX() - x, dy = obj->getY() - y;
        double distanceSq = dx * dx + dy * dy;

        if (distanceSq < MIN_DISTANCE * MIN_DISTANCE)
            distanceSq = MIN_DISTANCE * MIN_DISTANCE;

        double distance = sqrt(distanceSq);
        double accelMag = G * obj->getMass() / distanceSq;

        ax += accelMag * dx / distance;
        ay += accelMag * dy / distance;
    }
}

void SpaceObject::update(double timeStep)
{
    vx += ax * timeStep;
    vy += ay * timeStep;
    x += vx * timeStep;
    y += vy * timeStep;
}

void SpaceObject::setVelocity(double newVx, double newVy)
{
    vx = newVx;
    vy = newVy;
}

SpaceObject *SpaceObject::handleCollision(SpaceObject* obj1, SpaceObject* obj2) {
    // Calculate combined properties
    std::string newName = obj1->getMass() >= obj2->getMass() ? 
        obj1->getName() + "+" + obj2->getName() : 
        obj2->getName() + "+" + obj1->getName();

    double totalMass = obj1->getMass() + obj2->getMass();

    // Conservation of momentum
    double newVx = (obj1->getMass() * obj1->getVx() + obj2->getMass() * obj2->getVx()) / totalMass;
    double newVy = (obj1->getMass() * obj1->getVy() + obj2->getMass() * obj2->getVy()) / totalMass;

    // Position at center of mass
    double newX = (obj1->getMass() * obj1->getX() + obj2->getMass() * obj2->getX()) / totalMass;
    double newY = (obj1->getMass() * obj1->getY() + obj2->getMass() * obj2->getY()) / totalMass;

    // Blend colors
    sf::Color sfColor = blendColors(obj1->getColor(), obj2->getColor());

    // Calculate new radius based on combined area
    double r1 = obj1->getCollisionRadius();
    double r2 = obj2->getCollisionRadius();
    double newRadius = sqrt(r1 * r1 + r2 * r2);
    return new StellarObject(newName, newX, newY, newVx, newVy, totalMass, "Yellow", newRadius, sfColor);
}

sf::Color SpaceObject::blendColors(const string& color1, const string& color2) {
    map<string, sf::Color> colorMap = {
        {"yellow", sf::Color(255, 255, 51)},
        {"Yellow", sf::Color(255, 255, 51)},
        {"gray", sf::Color(192, 192, 192)},
        {"Gray", sf::Color(192, 192, 192)},
        {"grey", sf::Color(192, 192, 192)},
        {"Grey", sf::Color(192, 192, 192)},
        {"red", sf::Color(255, 69, 0)},
        {"Red", sf::Color(255, 69, 0)},
        {"blue", sf::Color(30, 144, 255)},
        {"Blue", sf::Color(30, 144, 255)},
        {"gold", sf::Color(255, 215, 0)},
        {"Gold", sf::Color(255, 215, 0)},
        {"lightblue", sf::Color(135, 206, 250)},
        {"LightBlue", sf::Color(135, 206, 250)},
        {"orange", sf::Color(255, 140, 0)},
        {"Orange", sf::Color(255, 140, 0)},
        {"green", sf::Color(0, 255, 0)},
        {"Green", sf::Color(0, 255, 0)},
        {"white", sf::Color(255, 255, 255)},
        {"White", sf::Color(255, 255, 255)}
    };
    sf::Color c1 = colorMap.count(color1) ? colorMap[color1] : sf::Color(255, 255, 255);
    sf::Color c2 = colorMap.count(color2) ? colorMap[color2] : sf::Color(255, 255, 255);
    sf::Color blended(
        (c1.r + c2.r) / 2,
        (c1.g + c2.g) / 2,
        (c1.b + c2.b) / 2
    );    
    return blended;
}

