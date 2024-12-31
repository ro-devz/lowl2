#ifndef NETWORK_MESSAGE_HPP
#define NETWORK_MESSAGE_HPP

#include <SFML/Network.hpp>
#include <string>

enum class MessageType : sf::Uint8 {
    OBJECT_UPDATE = 1,
    USER_INTERACTION = 2
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
};

#endif