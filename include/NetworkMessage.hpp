//============================================================================
// Name        : NetworkMessage.hpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================
#ifndef NETWORK_MESSAGE_HPP
#define NETWORK_MESSAGE_HPP

#include <SFML/Network.hpp>
#include <string>

enum class MessageType : sf::Uint8 {
    OBJECT_UPDATE = 1,
    USER_INTERACTION = 2,
    LEGEND_UPDATE = 3
};

struct UserInteraction {
    enum class Type : sf::Uint8 {
        MOUSE_DRAG = 1,
        MASS_CHANGE = 2,
        OBJECT_DELETE = 3,
        TIME_CHANGE = 4,
        THRUST = 5,
        OBJECT_SELECT = 6,
        VIEW_CHANGE = 7
    };

    Type type;
    std::string objectName;
    double x = 0.0;
    double y = 0.0;
    double value = 0.0;
};

struct LegendData {
    double timeStep;
    double totalElapsedTime;
    double viewOffsetX;
    double viewOffsetY;
};

class NetworkMessage {
public:
    static sf::Packet createUserInteractionPacket(const UserInteraction& interaction) {
        sf::Packet packet;
        packet << sf::Uint8(MessageType::USER_INTERACTION)
               << sf::Uint8(interaction.type)
               << interaction.objectName
               << interaction.x
               << interaction.y
               << interaction.value;
        return packet;
    }

    static sf::Packet createLegendUpdatePacket(const LegendData& legendData) {
        sf::Packet packet;
        packet << sf::Uint8(MessageType::LEGEND_UPDATE)
               << legendData.timeStep
               << legendData.totalElapsedTime
               << legendData.viewOffsetX
               << legendData.viewOffsetY;
        return packet;
    }
};

#endif