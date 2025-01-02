#ifndef SIMULATION_CLIENT_HPP
#define SIMULATION_CLIENT_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include "SpaceObject.hpp"
#include "NetworkMessage.hpp"
#include "Legend.hpp"

class SimulationClient
{
private:
    // Constants (declared first)
    const double SCREEN_WIDTH;
    const double SCREEN_HEIGHT;
    const double MAX_DISTANCE;
    const double MAX_RADIUS;
    const double DISTANCE_SCALE_RATIO;
    const double SIZE_SCALE_RATIO;
    const double SCALE;
    const double SIZE_SCALE;

    // SFML and networking members
    sf::RenderWindow window;
    sf::TcpSocket socket;
    std::thread networkThread;
    std::mutex objectsMutex;

    // Game state
    std::vector<SpaceObject *> objects;
    SpaceObject *selectedObject;
    sf::Vector2i lastMousePos;
    sf::Vector2i dragStartPos;
    double viewScale;
    bool isMouseDragging;
    bool isDraggingObject;
    bool isObjectSelected;
    bool running;
    double timeStep;
    double totalElapsedTime;
    LegendData currentLegendData;
    std::mutex legendMutex;
    Legend *legend;
    Legend *infoMenu;

    // Member functions
    void handleEvents();
    void receiveUpdates();
    void sendInteraction(const UserInteraction &interaction);
    void render(Legend *legend, Legend *infoMenu);

public:
    SimulationClient();
    ~SimulationClient();

    bool connect(const sf::IpAddress &address, unsigned short port = 8080);
    void disconnect();
    void run();
};

#endif