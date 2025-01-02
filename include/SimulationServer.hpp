#ifndef SIMULATION_SERVER_HPP
#define SIMULATION_SERVER_HPP

#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include "SpaceObject.hpp"
#include "NetworkMessage.hpp"

class SimulationServer
{
public:
    SimulationServer();
    ~SimulationServer();

    bool start();
    void stop();
    void run();

private:
    void initializeObjects();
    void handleClientMessages(sf::TcpSocket *client);
    void handleUserInteraction(const UserInteraction &interaction);
    void broadcastUpdate();
    void acceptClients();
    void updateLoop();

    std::vector<SpaceObject *> objects;
    std::vector<sf::TcpSocket *> clients;
    std::vector<std::thread> clientThreads;
    std::thread updateThread;
    std::thread acceptThread;

    sf::TcpListener listener;
    std::mutex objectsMutex;

    double realTimeStep;
    double totalElapsedTime;
    bool running;
};

#endif