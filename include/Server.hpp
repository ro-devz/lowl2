#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include "Simulation.hpp"
#include "NetworkMessage.hpp"

class Server {
private:
    sf::TcpListener listener;
    std::vector<sf::TcpSocket*> clients;
    Simulation& simulation;
    bool running;
    std::thread networkThread;

    void handleClientMessages();
    void broadcastUpdate();

public:
    Server(Simulation& sim) : simulation(sim), running(false) {}
    ~Server() {
        stop();
        for (auto* client : clients) {
            delete client;
        }
    }

    bool start() {
        if (listener.listen(53000) != sf::Socket::Done) {
            return false;
        }
        running = true;
        networkThread = std::thread(&Server::handleClientMessages, this);
        return true;
    }

    void stop() {
        running = false;
        if (networkThread.joinable()) {
            networkThread.join();
        }
        listener.close();
    }

    void update() {
        if (running) {
            broadcastUpdate();
        }
    }
};
#endif
