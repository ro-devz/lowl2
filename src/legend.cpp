#include "Legend.hpp"
#include <sstream>
#include <iomanip>

Legend::Legend(double screenWidth, double screenHeight, std::vector<SpaceObject*> objects)
    : screenWidth(screenWidth), screenHeight(screenHeight), objects(objects)
{
    if (!font.loadFromFile("font/Roboto-Black.ttf")) // Load a font (ensure the file is in the right directory)
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(11);  // Increased font size
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f);  // Set position to top-left corner, with some padding
}

void Legend::update(double timeStep, double totalElapsedTime, double centerX, double centerY)
{
    std::stringstream legendStream;

    // Time Step and Total Elapsed Time (in days)
    legendStream << "Time Step: " << toString(timeStep / 86400.0) << " days\n";  // Convert timeStep from seconds to days
    legendStream << "Elapsed Time: " << toString(totalElapsedTime / 86400.0) << " days\n";  // Convert totalElapsedTime to days

    // Center of the map coordinates (in km)
    legendStream << "Center: (" << toString(centerX / 1000.0) << " km, " << toString(centerY / 1000.0) << " km)\n";

    // Information about each object
    for (auto *obj : objects)
    {
        legendStream << obj->getName() << ": ";
        
        // If it's the Sun, set its position to (centerX, centerY)
        if (obj->getName() == "Sun") {
            legendStream << "Position: (" << toString(centerX / 1000.0) << " km, " 
                         << toString(centerY / 1000.0) << " km)\n";  // Convert from meters to km
        } else {
            // Otherwise, display the object's actual position
            legendStream << "Position: ("
                         << toString(obj->getX() / 1000.0) << " km, "
                         << toString(obj->getY() / 1000.0) << " km)\n";  // Convert from meters to km
        }
    }

    // Set the string for the legend text
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
