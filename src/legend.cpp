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
    text.setCharacterSize(13);  // Increased font size
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 10.f);  // Set position to top-left corner, with some padding
}

void Legend::update(double timeStep, double totalElapsedTime, double centerX, double centerY)
{
    std::stringstream legendStream;

    // Time Step and Total Elapsed Time
    legendStream << "Time Step: " << timeStep << " seconds\n";
    legendStream << "Elapsed Time: " << totalElapsedTime / 86400.0 << " days\n";  // Convert to days

    // Center of the map coordinates
    legendStream << "Center: (" << centerX << ", " << centerY << ")\n";

    // Information about each object
    for (auto *obj : objects)
    {
        legendStream << obj->getName() << ": ";
        legendStream << "Position: (" << obj->getX() << ", " << obj->getY() << ")\n";
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
