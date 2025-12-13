/*
** EPITECH PROJECT, 2025
** R_Type
** File description:
** Parser
*/

#include "Parser.hpp"
#include <iostream>
#include <sstream>
#include <span>

namespace client {
    bool Parser::_isValidIpPart(const std::string &s)
    {
        const int n = s.length();
        int num = 0;

        if (n == 0 || n > 3 || s[0] == '0' && n > 1)
            return false;
        for (const char c : s) {
            if (c < '0' || c > '9')
                return false;
        }
        for (const char c : s) {
            num = num * 10 + (c - '0');
        }
        return num >= 0 && num <= 255;
    }

    bool Parser::_isValidIp(const std::string &ip)
    {
        std::istringstream ss(ip);
        std::string part;
        int segmentCount = 0;
        while (std::getline(ss, part, '.'))
        {
            if (!_validPart(part))
                return false;
            segmentCount++;
        }
        return segmentCount == 4;
    }

    std::string Parser::getIp() const
    {
        return _ip;
    }

    bool Parser::isEveryArgValid(const int argc, char **args)
    {
        constexpr int minimumPort = 1024;

         if (argc != 3) {
             return false;
         }
         const auto arguments = std::span<char *>(args, argc);
         std::string_view const portString(arguments[1]);
         std::string_view const IPString(arguments[2]);
         try {
             int const unverifiedPort = std::stoi(std::string(portString));
             if (unverifiedPort > UINT16_MAX || unverifiedPort < minimumPort) {
                 return false;
             }
             this->port = unverifiedPort;

             if (!_isValidIp(IPString.data()))
                 return false;
             this->_ip = IPString.data();
             return true;
         } catch (std::exception &e) {
             return false;
         }
    }

    void Parser::_displayHelp() const
    {
        constexpr std::string_view programName{"r-type_clientr"};

        std::cout << "\n========================================\n";
        std::cout << "            R-Type Client Usage          \n";
        std::cout << "========================================\n\n";

        std::cout << "Usage:\n";
        std::cout << "  " << programName << " <port> <server_ip>\n\n";

        std::cout << "Arguments:\n";
        std::cout << "  <port>       TCP/UDP port number where the server run\n\n";
        std::cout << "  <server_ip>  ip address on which the server is launched.\n\n";

        std::cout << "Examples:\n";
        std::cout << "  " << programName << " 4242 127.0.0.1\n";
        std::cout << "  " << programName << " 8080 156.10.10.86\n\n";

        std::cout << "Notes:\n";
        std::cout << "  - Port must be a number between 1024 and 65535.\n";
        std::cout << "  - Ensure the port is not already in use.\n";
        std::cout << "  - Use Ctrl+C to stop the server.\n\n";

        std::cout << "========================================\n";
    }
}