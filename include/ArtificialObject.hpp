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

class ArtificialObject : public SpaceObject {
protected:
    double width, height;  // in (m)
    double thrustCapacity; // Thrust capacity in N
    // An artificial object shall be represented as a rectangle

public:
    ArtificialObject(const string &name, double x, double y, double vx, double vy, double mass, const string &color, double width, double height, double thrustCapacity);
    ~ArtificialObject() override = default;
   // double getWidth() {return width;}
   // double getheight() {return height;}

    void render(sf::RenderWindow &window, double scale, double centerX, double centerY, double maxDimension) const override;
};

#endif
