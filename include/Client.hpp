#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "Simulation.hpp"
#include "NetworkMessage.hpp"
#include <thread>
#include <mutex>

class Client {
private:
    sf::TcpSocket socket;
    Simulation& simulation;
    bool running;
    std::thread networkThread;
    std::mutex simulationMutex;

    void receiveUpdates() {
        while (running) {
            sf::Packet packet;
            if (socket.receive(packet) == sf::Socket::Done) {
                sf::Uint8 messageTypeRaw;
                packet >> messageTypeRaw;
                MessageType messageType = static_cast<MessageType>(messageTypeRaw);

                if (messageType == MessageType::OBJECT_UPDATE) {
                    sf::Uint32 objectCount;
                    packet >> objectCount;
                    
                    std::vector<SpaceObject*> updatedObjects;
                    for (sf::Uint32 i = 0; i < objectCount; ++i) {
                        std::string name, color;
                        double x, y, vx, vy, mass;
                        
                        packet >> name >> x >> y >> vx >> vy >> mass >> color;
                        
                        // Update simulation objects
                        std::lock_guard<std::mutex> lock(simulationMutex);
                        // Implementation depends on how you want to handle object updates
                    }
                }
            }
        }
    }

public:
    Client(Simulation& sim) : simulation(sim), running(false) {}
    
    ~Client() {
        stop();
    }

    bool connect(const sf::IpAddress& address, unsigned short port = 8080) {
        if (socket.connect(address, port) != sf::Socket::Done) {
            return false;
        }
        running = true;
        networkThread = std::thread(&Client::receiveUpdates, this);
        return true;
    }

    void stop() {
        running = false;
        if (networkThread.joinable()) {
            networkThread.join();
        }
        socket.disconnect();
    }

    void sendUserInteraction(const UserInteraction& interaction) {
        if (running) {
            sf::Packet packet = NetworkMessage::createUserInteractionPacket(interaction);
            socket.send(packet);
        }
    }
};

#endif