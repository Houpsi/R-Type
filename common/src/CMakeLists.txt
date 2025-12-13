add_library(r-type_common_lib
        shared_data/SharedData.cpp
        shared_data/SharedData.hpp
        packet_data/InputPacket.hpp
        enums/Key.hpp
        enums/KeyState.hpp
        custom_packet/CustomPacket.cpp
        custom_packet/CustomPacket.hpp
        parser/AParser.cpp
        parser/AParser.hpp
        packet_data/PacketData.hpp
        packet_data/PacketData.cpp
        shared_data/SharedData.cpp
        shared_data/SharedData.hpp
        packet_data/InputPacket.hpp
        packet_data/InputPacket.cpp
        packet_handler/PacketHandler.cpp
        packet_handler/PacketHandler.hpp
)

target_include_directories(r-type_common_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_common_lib
        PUBLIC
        sfml-network
)
