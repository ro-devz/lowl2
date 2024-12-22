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
    double radius; 

public:
    StellarObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double radius);
    ~StellarObject() override = default;
    void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxRadius) const override;
    virtual bool isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const override;
};

#endif
