add_executable(rtype_common_tests
        TestDataTranslator.cpp
        TestPacketFactory.cpp
        TestBitPacking.cpp
        TestPacketDisassembler.cpp
)

target_link_libraries(rtype_common_tests
        PRIVATE
        r-type_common_lib
        gtest
        gtest_main
)

target_include_directories(rtype_common_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME MyTests COMMAND rtype_common_tests)
