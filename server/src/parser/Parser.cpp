/*
** EPITECH PROJECT, 2025
** r-type_server
** File description:
** Parser
*/
#include "Parser.hpp"
#include <iostream>
#include <span>
#include <string>

namespace server {
    bool Parser::isEveryArgValid(int argc, char **args)
    {
        constexpr int minimumPort = 1024;

         if (argc != 2) {
             return false;
         }
         auto arguments = std::span<char *>(args, argc);
         std::string_view const portString(arguments[1]);
         try {
             int const unverifiedPort = std::stoi(std::string(portString));
             if (unverifiedPort > UINT16_MAX || unverifiedPort < minimumPort) {
                 return false;
             }
             this->port = unverifiedPort;
             return true;
         } catch (std::exception &e) {
             return false;
         }
    }

    void Parser::_displayHelp() const
    {
        constexpr std::string_view programName{"r-type_server"};

        std::cout << "\n========================================\n";
        std::cout << "            R-Type Server Usage          \n";
        std::cout << "========================================\n\n";

        std::cout << "Usage:\n";
        std::cout << "  " << programName << " <port>\n\n";

        std::cout << "Arguments:\n";
        std::cout << "  <port>       TCP/UDP port number to start the server on.\n\n";

        std::cout << "Examples:\n";
        std::cout << "  " << programName << " 4242\n";
        std::cout << "  " << programName << " 8080\n\n";

        std::cout << "Notes:\n";
        std::cout << "  - Port must be a number between 1024 and 65535.\n";
        std::cout << "  - Ensure the port is not already in use.\n";
        std::cout << "  - Use Ctrl+C to stop the server.\n\n";

        std::cout << "========================================\n";
    }
}// namespace server