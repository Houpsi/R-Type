/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** PacketData
*/


#include "PacketData.hpp"
#include "Constants.hpp"

namespace cmn {

    sf::Packet &operator<<(sf::Packet &packet, const packetContent &content)
    {
        packet << content.index();

        std::visit([&packet](auto &&arg){
            packet << arg;
        }, content);

        return packet;
    }

    sf::Packet &operator>>(sf::Packet &packet, packetContent &data)
    {
        std::size_t typeIndex = 0;
        packet >> typeIndex;

        switch (typeIndex) {
            case connectionProtocolId: {
                connectionPacket connection{};
                packet >> connection;
                data = connection;
                break;
            }
            case inputProtocolId: {
                inputPacket input{};
                packet >> input;
                data = input;
                break;
            }
            case positionProtocolId: {
                positionPacket position{};
                packet >> position;
                data = position;
                break;
            }
            case newEntityProtocolId: {
                newEntityPacket newEntity{};
                packet >> newEntity;
                data = newEntity;
                break;
            }
            case deleteEntityProtocolId: {
                deleteEntityPacket deleteEntity{};
                packet >> deleteEntity;
                data = deleteEntity;
                break;
            }
            case startGameProtocolId: {
                startGamePacket startGame{};
                packet >> startGame;
                data = startGame;
                break;
            }
            default: {
                return packet;
            }
        }

        return packet;
    }

    sf::Packet &operator<<(sf::Packet &packet, const packetData &data)
    {
        return packet << data.packetId << data.content;
    }

    sf::Packet &operator>>(sf::Packet &packet, packetData &data)
    {
        return packet >> data.packetId >> data.content;
    }

}// namespace cmn