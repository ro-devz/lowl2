//============================================================================
// Name        : StellarObject.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#ifndef STELLAR_OBJECT_HPP
#define STELLAR_OBJECT_HPP

#include "SpaceObject.hpp"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class StellarObject : public SpaceObject
{
protected:
    double radius; // Radius of the stellar object
    //dSpaceObject* parent;  // Parent object for orbital motion (if any)

public:
    StellarObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double radius);
    ~StellarObject() override = default;
    // void setParent(SpaceObject *newParent) { parent = newParent; }

    //SpaceObject* getParent() const { return parent; }

  // double getRadius(){ return radius; }
    void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxRadius) const override;
    //void update(double timeStep) override;
};

#endif
