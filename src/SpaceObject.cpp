//============================================================================
// Name        : SpaceObject.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#include "SpaceObject.hpp"

double SpaceObject::viewOffsetX = 0.0;
double SpaceObject::viewOffsetY = 0.0;

SpaceObject::SpaceObject(const string &name, double x, double y, double vx, 
                         double vy, double mass, const string &color)
    : name(name), color(color), x(x), y(y), vx(vx), vy(vy), ax(0), ay(0), 
      mass(mass), radius(0) {}

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
        if (obj == this) continue;

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

 void SpaceObject::setVelocity(double newVx, double newVy) {
        vx = newVx;
        vy = newVy;
    }
