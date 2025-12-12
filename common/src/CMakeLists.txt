add_library(r-type_common_lib
        shared_data/SharedData.cpp
        shared_data/SharedData.hpp
        packet_data/InputPacket.hpp
        enums/Key.hpp
        enums/KeyState.hpp
        custom_packet/CustomPacket.cpp
        custom_packet/CustomPacket.hpp
        packet_data/PacketData.hpp
        shared_data/SharedData.cpp
        shared_data/SharedData.hpp
)

target_include_directories(r-type_common_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(r-type_common_lib
        PUBLIC
        sfml-network
)
