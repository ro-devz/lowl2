//============================================================================
// Name        : SimulationClient.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#include "SimulationClient.hpp"
#include "NetworkMessage.hpp"
#include "ArtificialObject.hpp"
#include "StellarObject.hpp"
#include "Legend.hpp"
#include <SFML/Network.hpp>
#include <iostream>

SimulationClient::SimulationClient()
    : SCREEN_WIDTH(1200.0),
      SCREEN_HEIGHT(800.0),
      MAX_DISTANCE(4.49825e12),
      MAX_RADIUS(696340.0e3),
      DISTANCE_SCALE_RATIO(10.0),
      SIZE_SCALE_RATIO(20000.0),
      SCALE(MAX_DISTANCE / (SCREEN_WIDTH * DISTANCE_SCALE_RATIO)),
      SIZE_SCALE(MAX_RADIUS / SIZE_SCALE_RATIO),
      window(sf::VideoMode(1200, 800), "Space Simulation Client"),
      selectedObject(nullptr),
      viewScale(1.0),
      isMouseDragging(false),
      isDraggingObject(false),
      isObjectSelected(false),
      running(false)
{
    window.setFramerateLimit(60);
}

SimulationClient::~SimulationClient()
{
    disconnect();
    for (auto *obj : objects)
    {
        delete obj;
    }
}

bool SimulationClient::connect(const sf::IpAddress &address, unsigned short port)
{
    std::cout << "Connecting to server at " << address << ":" << port << std::endl;
    if (socket.connect(address, port) != sf::Socket::Done)
    {
        std::cerr << "Connection failed!" << std::endl;
        return false;
    }
    std::cout << "Connected successfully!" << std::endl;
    running = true;
    networkThread = std::thread(&SimulationClient::receiveUpdates, this);
    return true;
}

void SimulationClient::disconnect()
{
    running = false;
    if (networkThread.joinable())
    {
        networkThread.join();
    }
    socket.disconnect();
}

void SimulationClient::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && selectedObject)
            {
                isDraggingObject = true;
                dragStartPos = sf::Mouse::getPosition(window);
            }

            if (event.mouseButton.button == sf::Mouse::Middle)
            {
                isMouseDragging = true;
                lastMousePos = sf::Mouse::getPosition(window);
            }

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                double mouseX = event.mouseButton.x;
                double mouseY = event.mouseButton.y;

                SpaceObject *clickedObject = nullptr;
                for (auto *obj : objects)
                {
                    if (obj->isClicked(mouseX, mouseY, SCALE / viewScale,
                                       window.getSize().x / 2.0, window.getSize().y / 2.0, SIZE_SCALE))
                    {
                        clickedObject = obj;
                        break;
                    }
                }

                if (clickedObject && !isObjectSelected)
                {
                    selectedObject = clickedObject;
                    isObjectSelected = true;
                    cout << "Selected object: " << selectedObject->getName() << endl;

                    UserInteraction interaction;
                    interaction.type = UserInteraction::Type::OBJECT_SELECT;
                    interaction.objectName = clickedObject->getName();
                    cout << "Sending object selection to server" << endl;
                    cout << "Object name: " << interaction.objectName << endl;
                    sendInteraction(interaction);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                isDraggingObject = false;

            if (event.mouseButton.button == sf::Mouse::Middle)
                isMouseDragging = false;
        }
        else if (event.type == sf::Event::MouseMoved && isMouseDragging)
        {
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
            sf::Vector2i delta = currentMousePos - lastMousePos;

            double worldDeltaX = -delta.x * SCALE / viewScale;
            double worldDeltaY = -delta.y * SCALE / viewScale;

            SpaceObject::updateViewOffset(worldDeltaX, worldDeltaY);
            lastMousePos = currentMousePos;

            UserInteraction interaction;
            interaction.type = UserInteraction::Type::VIEW_CHANGE;
            interaction.x = worldDeltaX;
            interaction.y = worldDeltaY;
            sendInteraction(interaction);
        }
        else if (event.type == sf::Event::MouseMoved && isDraggingObject && selectedObject)
        {
            sf::Vector2i currentPos = sf::Mouse::getPosition(window);
            sf::Vector2i delta = currentPos - dragStartPos;

            double worldDeltaX = delta.x * SCALE / viewScale;
            double worldDeltaY = delta.y * SCALE / viewScale;

            UserInteraction interaction;
            interaction.type = UserInteraction::Type::MOUSE_DRAG;
            interaction.objectName = selectedObject->getName();
            interaction.x = selectedObject->getX() + worldDeltaX;
            interaction.y = selectedObject->getY() + worldDeltaY;
            sendInteraction(interaction);

            dragStartPos = currentPos;
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta > 0)
                viewScale *= 1.1;
            else
                viewScale *= 0.9;

            viewScale = std::max(0.0001, std::min(viewScale, 100.0));
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (selectedObject)
            {
                if (event.key.code == sf::Keyboard::Delete)
                {
                    UserInteraction interaction;
                    interaction.type = UserInteraction::Type::OBJECT_DELETE;
                    interaction.objectName = selectedObject->getName();
                    sendInteraction(interaction);

                    selectedObject = nullptr;
                    isObjectSelected = false;
                }
                else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Subtract)
                {
                    UserInteraction interaction;
                    interaction.type = UserInteraction::Type::MASS_CHANGE;
                    interaction.objectName = selectedObject->getName();
                    interaction.value = (event.key.code == sf::Keyboard::Add) ? 1.1 : 0.9;
                    sendInteraction(interaction);
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    selectedObject = nullptr;
                    isObjectSelected = false;
                }
            }
            else
            {
                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Subtract)
                {
                    UserInteraction interaction;
                    interaction.type = UserInteraction::Type::TIME_CHANGE;
                    interaction.value = (event.key.code == sf::Keyboard::Add) ? 3600.0 : -3600.0;
                    sendInteraction(interaction);
                }
            }
        }
    }
}

void SimulationClient::sendInteraction(const UserInteraction &interaction)
{
    if (running)
    {
        sf::Packet packet = NetworkMessage::createUserInteractionPacket(interaction);
        socket.send(packet);
    }
}

void SimulationClient::render(Legend *legend, Legend *infoMenu)
{
    window.clear(sf::Color::Black);

    {
        std::lock_guard<std::mutex> lockObjects(objectsMutex);
        for (auto *obj : objects)
        {
            obj->render(window, SCALE / viewScale,
                        window.getSize().x / 2.0,
                        window.getSize().y / 2.0,
                        SIZE_SCALE);
        }
    }

    {
        std::lock_guard<std::mutex> lockLegend(legendMutex);
        legend->update(currentLegendData.timeStep,
                       currentLegendData.totalElapsedTime,
                       currentLegendData.viewOffsetX,
                       currentLegendData.viewOffsetY);
        legend->render(window);

        infoMenu->updateObject(selectedObject);
        infoMenu->render(window);
    }

    window.display();
}

void SimulationClient::receiveUpdates()
{
    while (running)
    {
        sf::Packet packet;
        sf::Socket::Status status = socket.receive(packet);

        if (status == sf::Socket::Done)
        {
            sf::Uint8 messageTypeRaw;
            packet >> messageTypeRaw;
            MessageType messageType = static_cast<MessageType>(messageTypeRaw);

            if (messageType == MessageType::OBJECT_UPDATE)
            {
                sf::Uint32 objectCount;
                packet >> objectCount;

                std::vector<SpaceObject *> newObjects;
                newObjects.reserve(objectCount);

                std::string selectedName = selectedObject ? selectedObject->getName() : "";

                try
                {
                    for (sf::Uint32 i = 0; i < objectCount; ++i)
                    {
                        std::string name, color;
                        double x, y, vx, vy, mass;
                        bool isArtificial;

                        packet >> name >> x >> y >> vx >> vy >> mass >> color >> isArtificial;

                        SpaceObject *obj = nullptr;
                        if (isArtificial)
                        {
                            double width, height;
                            packet >> width >> height;
                            obj = new ArtificialObject(name, x, y, vx, vy, mass, color, width, height, 0);
                        }
                        else
                        {
                            double radius;
                            packet >> radius;
                            obj = new StellarObject(name, x, y, vx, vy, mass, color, radius);
                        }

                        if (obj)
                            newObjects.push_back(obj);
                    }
                    {
                        std::lock_guard<std::mutex> lock(objectsMutex);

                        selectedObject = nullptr;

                        for (auto *obj : objects)
                        {
                            delete obj;
                        }
                        objects.clear();

                        objects = std::move(newObjects);

                        // Restore selected object if it still exists
                        if (!selectedName.empty())
                        {
                            for (auto *obj : objects)
                            {
                                // Check for exact match or merged object containing the name
                                if (obj->getName() == selectedName ||
                                    obj->getName().find(selectedName) != std::string::npos)
                                {
                                    selectedObject = obj;
                                    break;
                                }
                            }

                            if (!selectedObject)
                            {
                                isObjectSelected = false;
                            }
                        }

                        if (legend)
                            legend->setObjects(objects);
                        if (infoMenu)
                            infoMenu->setObjects(objects);
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error processing update: " << e.what() << std::endl;
                    for (auto *obj : newObjects)
                    {
                        delete obj;
                    }
                }
            }
            else if (messageType == MessageType::LEGEND_UPDATE)
            {
                std::lock_guard<std::mutex> lock(legendMutex);
                packet >> currentLegendData.timeStep >> currentLegendData.totalElapsedTime >> currentLegendData.viewOffsetX >> currentLegendData.viewOffsetY;
            }
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cout << "Server disconnected" << std::endl;
            running = false;
            break;
        }
    }
}

void SimulationClient::run()
{
    legend = new Legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects, 10.f, 10.f);
    infoMenu = new Legend(SCREEN_WIDTH, SCREEN_HEIGHT, objects, SCREEN_WIDTH - 300.f, 10.f);

    sf::Clock clock;
    while (window.isOpen() && running)
    {
        handleEvents();
        render(legend, infoMenu);
    }

    delete legend;
    delete infoMenu;
}