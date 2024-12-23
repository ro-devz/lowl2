#include "Legend.hpp"
#include <sstream>
#include <iomanip>

Legend::Legend(double screenWidth, double screenHeight, std::vector<SpaceObject *> objects, float x, float y)
    : screenWidth(screenWidth), screenHeight(screenHeight), objects(objects)
{
    font.loadFromFile("font/Roboto-Black.ttf");
    text.setFont(font);
    text.setCharacterSize(11); // Increased font size
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y); // Set position to top-left corner, with some padding
}

void Legend::update(double timeStep, double totalElapsedTime, double viewOffsetX, double viewOffsetY)
{
    std::stringstream legendStream;

    legendStream << "Time Step: " << toString(timeStep / 86400.0) << " days\n";
    legendStream << "Elapsed Time: " << toString(totalElapsedTime / 86400.0) << " days\n";

    // Show view center in astronomical coordinates
    legendStream << "View Center: ("
                 << toString(viewOffsetX / 1000.0) << " km, "
                 << toString(viewOffsetY / 1000.0) << " km)\n\n";

    // Show object positions relative to the Sun at (0,0)
    for (auto *obj : objects)
    {
        legendStream << obj->getName() << ": ";
        legendStream << "Position: ("
                     << toString(obj->getX() / 1000.0) << " km, "
                     << toString(obj->getY() / 1000.0) << " km)\n";
    }

    text.setString(legendStream.str());
}

void Legend::updateObject(SpaceObject *selectedObject)
{

    std::stringstream legendStream;
    if (selectedObject)
    {
        legendStream << "Selected Object:\n";
        legendStream << "Name: " << selectedObject->getName() << "\n";
        legendStream << "Position: (" << toString(selectedObject->getX() / 1000.0) << " km, "
                     << toString(selectedObject->getY() / 1000.0) << " km)\n";
        legendStream << "Mass: " << toString(selectedObject->getMass()) << " kg\n";
    }
    else
    {
        legendStream << "No object selected.\n";
    }

    text.setString(legendStream.str());
}
void Legend::render(sf::RenderWindow &window)
{
    // Draw the legend on the screen
    window.draw(text);
}

// Helper function to convert a number to string
std::string Legend::toString(double number)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << number;
    return ss.str();
}
