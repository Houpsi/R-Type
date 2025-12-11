/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** SharedData
*/

#ifndef R_TYPE_SHAREDDATA_HPP
#define R_TYPE_SHAREDDATA_HPP

#include <mutex>
#include <optional>
#include <queue>
#include <unordered_map>
#include "../packet_data/PacketData.hpp"

namespace server {
    /**
     * @brief Class used to safely share data across multiple threads.
     *
     * It manages two packet queues (received and to send) and a list of players,
     * using a mutex to guarantee the safety of concurrent access.
     */
    class SharedData {
        public:
            /**
             * @brief Adds a received packet to the queue.
             * @param data The received packet data (PacketData).
             */
            void addReceivedPacket(const PacketData &data);

            /**
             * @brief Retrieves and removes the first received packet from the queue.
             * @return An optional containing the PacketData if available, otherwise std::nullopt.
             */
            std::optional<PacketData> getReceivedPacket();

            /**
             * @brief Adds a packet to be sent to the queue.
             * @param data The packet data (PacketData) to send.
             */
            void addSendPacket(const PacketData &data);

            /**
             * @brief Retrieves and removes the first packet to be sent from the queue.
             * @return An optional containing the PacketData if available, otherwise std::nullopt.
             */
            std::optional<PacketData> getSendPacket();

            /**
             * @brief Adds a new player to the list.
             * @param playerId The unique identifier of the player.
             * @param port The connection port of the player.
             * @param ipAddress The IP address of the player.
             */
            void addPlayer(int playerId, int port, const std::string &ipAddress);

            /**
             * @brief Retrieves the connection information (port and IP) of a player.
             * @param playerId The unique identifier of the player.
             * @return An optional containing a pair (port, IP address) if found, otherwise std::nullopt.
             */
            std::optional<std::pair<int, std::string>> getPlayer(int playerId);

        private:
            std::queue<PacketData> _receivedQueue; ///< Queue for received packets (to be processed).
            std::queue<PacketData> _sendQueue;     ///< Queue for packets to be sent.
            std::mutex _mutex;                     ///< Mutex for synchronizing data access.
            /**
             * @brief List of connected players.
             * The key is the player ID (int), the value is a pair (port, IP address).
             */
            std::unordered_map<int, std::pair<int, std::string>> _playerList;
    };
}

#endif //R_TYPE_SHAREDDATA_HPP