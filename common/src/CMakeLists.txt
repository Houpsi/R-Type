add_library(r-type_common_lib
        parser/AParser.cpp
        parser/AParser.hpp
)

target_include_directories(r-type_common_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)