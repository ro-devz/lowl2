//============================================================================
// Name        : ArtificialObject.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#ifndef ARTIFICIAL_OBJECT_HPP
#define ARTIFICIAL_OBJECT_HPP

#include "SpaceObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;

class ArtificialObject : public SpaceObject
{
protected:
    double width, height;  // in (m)
    double thrustCapacity; // Thrust capacity in N

public:
    ArtificialObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double width, double height, double thrustCapacity);
    ~ArtificialObject() override = default;
    void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxDimension) const override;
    virtual bool isClicked(double mouseX, double mouseY, double scale, double centerX, double centerY, double sizeScale) const override;

    void applyThrust(double dx, double dy) {
        // Apply thrust in the opposite direction of arrow keys
        double thrustX = -dx * thrustCapacity / mass;
        double thrustY = -dy * thrustCapacity / mass;
        setAcceleration(ax + thrustX, ay + thrustY);
    }

    bool isArtificial() const { return true; }
    virtual double getCollisionRadius() const override { 
        return sqrt(width * width + height * height) / 2; 
    }
};

#endif
