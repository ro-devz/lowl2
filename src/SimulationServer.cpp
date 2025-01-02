//============================================================================
// Name        : SimulationServer.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#include "SimulationServer.hpp"
#include "StellarObject.hpp"
#include "ArtificialObject.hpp"
#include "NetworkMessage.hpp"

SimulationServer::SimulationServer()
    : realTimeStep(86000.0), totalElapsedTime(0.0), running(false)
{
    initializeObjects();
}

void SimulationServer::initializeObjects()
{
    // Sun
    StellarObject *sun = new StellarObject("Sun", 0, 0, 0, 0, 1.989e30, "Yellow", 696340.0e3);

    // Planets
    StellarObject *mercury = new StellarObject("Mercury", 57.91e9, 0, 0, 47.872e3, 3.3011e23, "Gray", 4879.0e3);
    StellarObject *venus = new StellarObject("Venus", 108.2e9, 0, 0, 35.02e3, 4.8675e24, "Yellow", 12104.0e3);
    StellarObject *earth = new StellarObject("Earth", 149.6e9, 0, 0, 29.783e3, 5.9724e24, "Blue", 12742.0e3);
    StellarObject *mars = new StellarObject("Mars", 227.94e9, 0, 0, 24.077e3, 6.4171e23, "Red", 6779.0e3);
    StellarObject *jupiter = new StellarObject("Jupiter", 778.5e9, 0, 0, 13.07e3, 1.8982e27, "Orange", 139820.0e3);
    StellarObject *saturn = new StellarObject("Saturn", 1.4294e12, 0, 0, 9.687e3, 5.6834e26, "Gold", 116460.0e3);
    StellarObject *uranus = new StellarObject("Uranus", 2.87099e12, 0, 0, 6.81e3, 8.6810e25, "LightBlue", 50724.0e3);
    StellarObject *neptune = new StellarObject("Neptune", 4.49825e12, 0, 0, 5.43e3, 1.02413e26, "Blue", 49244.0e3);

    // Moons
    const double EARTH_RADIUS = 12742.e03; // Average radius of Earth
    double moonOrbitSpeed = sqrt((6.67430e-11 * earth->getMass()) / 384400.0e3);
    StellarObject *moon = new StellarObject("Moon",
                                            earth->getX() + 384400.0e3,
                                            earth->getY(),
                                            0,
                                            29.783e3 + moonOrbitSpeed,
                                            7.342e22, "Gray", 1737.4e3);

    double europaOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 0.671e9);
    StellarObject *europa = new StellarObject("Europa",
                                              jupiter->getX() + 0.671e9,
                                              jupiter->getY(),
                                              0,
                                              13.07e3 + europaOrbitSpeed,
                                              4.7998e22, "White", 1560.8e3);

    double ioOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 0.422e9);
    StellarObject *io = new StellarObject("Io",
                                          jupiter->getX() + 0.422e9,
                                          jupiter->getY(),
                                          0,
                                          13.07e3 + ioOrbitSpeed,
                                          8.9319e22, "Yellow", 1821.6e3);

    double ganymedeOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 1.07e9);
    StellarObject *ganymede = new StellarObject("Ganymede",
                                                jupiter->getX() + 1.07e9,
                                                jupiter->getY(),
                                                0,
                                                13.07e3 + ganymedeOrbitSpeed,
                                                1.4819e23, "Gray", 2634.1e3);

    // Callisto (Jupiter's moon)
    double callistoOrbitSpeed = sqrt((6.67430e-11 * jupiter->getMass()) / 1.883e9);
    StellarObject *callisto = new StellarObject("Callisto",
                                                jupiter->getX() + 1.883e9,
                                                jupiter->getY(),
                                                0,
                                                13.07e3 + callistoOrbitSpeed,
                                                1.0759e23, "Gray", 2410.3e3);

    // Titan (Saturn's moon)
    double titanOrbitSpeed = sqrt((6.67430e-11 * saturn->getMass()) / 1.22e9);
    StellarObject *titan = new StellarObject("Titan",
                                             saturn->getX() + 1.22e9,
                                             saturn->getY(),
                                             0,
                                             9.687e3 + titanOrbitSpeed,
                                             1.3452e23, "Yellow", 2574.7e3);

    ArtificialObject *iss = new ArtificialObject("ISS",
                                                 earth->getX() + (EARTH_RADIUS + 408e3),
                                                 earth->getY(),
                                                 0,
                                                 earth->getVy() + 7.66e3,
                                                 419725,
                                                 "White",
                                                 109,
                                                 51,
                                                 4e4);

    // Hubble Space Telescope
    // Orbits at about 540km above Earth's surface
    ArtificialObject *hubble = new ArtificialObject("Hubble",
                                                    earth->getX() + (EARTH_RADIUS + 540e3),
                                                    earth->getY(),
                                                    0,
                                                    earth->getVy() + 7.5e3,
                                                    11110,
                                                    "Gray",
                                                    13.2,
                                                    4.2,
                                                    2e4);

    // GPS Satellites
    // Orbit at about 20,200km above Earth's surface
    ArtificialObject *gps = new ArtificialObject("GPS",
                                                 earth->getX() + (EARTH_RADIUS + 20200e3),
                                                 earth->getY(),
                                                 0,
                                                 earth->getVy() + 3.87e3,
                                                 1630,
                                                 "White",
                                                 5.3,
                                                 2.7,
                                                 1e4);

    // James Webb Space Telescope
    // Located at L2 point, approximately 1.5 million km from Earth
    ArtificialObject *jwst = new ArtificialObject("JWST",
                                                  earth->getX() + 1.5e9, // L2 point
                                                  earth->getY(),
                                                  0,
                                                  earth->getVy() + 0.2e3,
                                                  6500,
                                                  "Green",
                                                  21,
                                                  14,
                                                  1e4);

    objects = {sun, earth, moon, europa, io, mercury, venus, mars, jupiter, saturn, uranus, neptune, ganymede, callisto, titan, iss, hubble, gps, jwst};
}

SimulationServer::~SimulationServer()
{
    stop();
    for (auto *obj : objects)
    {
        delete obj;
    }
    for (auto *client : clients)
    {
        delete client;
    }
}

bool SimulationServer::start() {
    unsigned short port = 8080;
    
    stop();
    
    sf::Socket::Status status = listener.listen(port);
    if (status != sf::Socket::Done) {
        std::cerr << "Error: Failed to start listener on port " << port 
                  << " with status code: " << status << std::endl;
        return false;
    }
    
    std::cout << "Server listening on port " << port << std::endl;
    running = true;
    
    try {
        updateThread = std::thread(&SimulationServer::updateLoop, this);
        acceptThread = std::thread(&SimulationServer::acceptClients, this);
    } catch (const std::exception& e) {
        std::cerr << "Failed to start server threads: " << e.what() << std::endl;
        stop();
        return false;
    }
    
    return true;
}

void SimulationServer::stop() {
    running = false;
    
    listener.close();
    
    std::lock_guard<std::mutex> lock(objectsMutex);
    for (auto* client : clients) {
        client->disconnect();
        delete client;
    }
    clients.clear();
    
    if (updateThread.joinable()) {
        updateThread.join();
    }
    if (acceptThread.joinable()) {
        acceptThread.join();
    }
    for (auto& thread : clientThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    clientThreads.clear();
}


void SimulationServer::acceptClients() {
    while (running) {
        try {
            sf::TcpSocket* client = new sf::TcpSocket;
            sf::Socket::Status status = listener.accept(*client);
            
            if (status == sf::Socket::Done) {
                std::cout << "New client connected from: " 
                          << client->getRemoteAddress() << std::endl;
                std::lock_guard<std::mutex> lock(objectsMutex);
                clients.push_back(client);
                clientThreads.emplace_back(&SimulationServer::handleClientMessages, this, client);
            } else {
                delete client;
                if (running) {
                    std::cerr << "Failed to accept connection, status: " << status << std::endl;
                }
            }
        } catch (const std::exception& e) {
            if (running) {  
                std::cerr << "Exception in acceptClients: " << e.what() << std::endl;
            }
        }
    }
}

void SimulationServer::updateLoop() {
    sf::Clock clock;
    while (running) {
        float deltaTime = clock.restart().asSeconds();
        double adjustedTimeStep = realTimeStep * deltaTime;
        {
            std::lock_guard<std::mutex> lock(objectsMutex);
            
            bool collisionOccurred = false;
            SpaceObject *obj1 = nullptr;
            SpaceObject *obj2 = nullptr;

            for (size_t i = 0; i < objects.size() && !collisionOccurred; i++) {
                for (size_t j = i + 1; j < objects.size() && !collisionOccurred; j++) {
                    if (!objects[i] || !objects[j]) continue;
                    
                    double dx = objects[i]->getX() - objects[j]->getX();
                    double dy = objects[i]->getY() - objects[j]->getY();
                    double distance = sqrt(dx * dx + dy * dy);

                    if (distance < (objects[i]->getCollisionRadius() + objects[j]->getCollisionRadius())) {
                        collisionOccurred = true;
                        obj1 = objects[i];
                        obj2 = objects[j];
                    }
                }
            }

            if (collisionOccurred && obj1 && obj2) {
                try {
                    SpaceObject* newObject = SpaceObject::handleCollision(obj1, obj2);
                    
                    if (newObject) {
                        // Remove old objects
                        for (auto& obj : objects) {
                            if (obj == obj1 || obj == obj2) {
                                delete obj; // Delete memory
                                obj = nullptr; // Nullify the pointer
                            }
                        }

                        // Remove null pointers from the list
                        objects.erase(
                            std::remove(objects.begin(), objects.end(), nullptr),
                            objects.end()
                        );

                        objects.push_back(newObject);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Collision handling error: " << e.what() << std::endl;
                }
            }

            for (auto* obj : objects) {
                if (obj) obj->computeGravitationalForces(objects);
            }

            for (auto* obj : objects) {
                if (obj) obj->update(adjustedTimeStep);
            }

            totalElapsedTime += adjustedTimeStep;
        }

        broadcastUpdate();

        sf::sleep(sf::milliseconds(16)); // ~60 FPS
    }
}


void SimulationServer::handleUserInteraction(const UserInteraction &interaction)
{
    SpaceObject *targetObj = nullptr;
    for (auto *obj : objects)
    {
        if (obj->getName() == interaction.objectName)
        {
            targetObj = obj;
            break;
        }
    }
    if (targetObj || interaction.type == UserInteraction::Type::TIME_CHANGE)
    {
        switch (interaction.type)
        {
        case UserInteraction::Type::MOUSE_DRAG:
            targetObj->setPosition(interaction.x, interaction.y);
            break;

        case UserInteraction::Type::MASS_CHANGE:
            targetObj->adjustMass(interaction.value);
            break;

        case UserInteraction::Type::OBJECT_DELETE:
            objects.erase(std::remove(objects.begin(), objects.end(), targetObj), objects.end());
            delete targetObj;
            break;

        case UserInteraction::Type::TIME_CHANGE:
            realTimeStep += interaction.value;
            break;

        case UserInteraction::Type::THRUST:
            if (auto *artificial = dynamic_cast<ArtificialObject*>(targetObj))
            {
                artificial->applyThrust(interaction.x, interaction.y);
            }
            break;

        default:
            break;
        }
    }
}
void SimulationServer::handleClientMessages(sf::TcpSocket *client)
{
    while (running)
    {
        sf::Packet packet;
        if (client->receive(packet) == sf::Socket::Done)
        {
            sf::Uint8 messageTypeRaw;
            packet >> messageTypeRaw;
            MessageType messageType = static_cast<MessageType>(messageTypeRaw);
            if (messageType == MessageType::USER_INTERACTION)
            {
                UserInteraction interaction;
                sf::Uint8 typeRaw;
                packet >> typeRaw >> interaction.objectName >> interaction.x >> interaction.y >> interaction.value;
                interaction.type = static_cast<UserInteraction::Type>(typeRaw);
                std::lock_guard<std::mutex> lock(objectsMutex);
                handleUserInteraction(interaction);
            }
        }
    }
}


void SimulationServer::broadcastUpdate() {
    sf::Packet objectPacket;
    objectPacket << sf::Uint8(MessageType::OBJECT_UPDATE);
    
    {
        std::lock_guard<std::mutex> lock(objectsMutex);
        size_t validObjectCount = std::count_if(objects.begin(), objects.end(),
            [](SpaceObject* obj) { return obj != nullptr; });
            
        objectPacket << sf::Uint32(validObjectCount);

        for (const auto* obj : objects) {
            if (!obj) continue;
            
            objectPacket << obj->getName()
                        << obj->getX()
                        << obj->getY()
                        << obj->getVx()
                        << obj->getVy()
                        << obj->getMass()
                        << obj->getColor()
                        << (dynamic_cast<const ArtificialObject*>(obj) != nullptr);

            if (auto artificial = dynamic_cast<const ArtificialObject*>(obj)) {
                objectPacket << artificial->getWidth()
                            << artificial->getHeight();
                            //<< artificial->getThrustCapacity();
            }
            else if (auto stellar = dynamic_cast<const StellarObject*>(obj)) {
                objectPacket << stellar->getRadius();
            }
        }
    }
    LegendData legendData{
        realTimeStep,
        totalElapsedTime,
        SpaceObject::getViewOffsetX(),
        SpaceObject::getViewOffsetY()
    };
    sf::Packet legendPacket = NetworkMessage::createLegendUpdatePacket(legendData);

    std::lock_guard<std::mutex> lock(objectsMutex);
    auto it = clients.begin();
    while (it != clients.end()) {
        bool clientValid = true;
        
        if ((*it)->send(objectPacket) != sf::Socket::Done ||
            (*it)->send(legendPacket) != sf::Socket::Done) {
            clientValid = false;
        }

        if (!clientValid) {
            std::cout << "Client disconnected. Removing from list." << std::endl;
            delete *it;
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}

void SimulationServer::run()
{
    std::cout << "Server running on port 8080" << std::endl;

    if (!start())
    {
        std::cout << "Failed to start server" << std::endl;
        return;
    }

    std::string input;
    while (running)
    {
        std::getline(std::cin, input);
        if (input == "quit" || input == "exit")
        {
            running = false;
        }
    }

    stop();
}