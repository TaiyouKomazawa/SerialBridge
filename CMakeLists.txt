cmake_minimum_required(VERSION 3.00)
project(serial_bridge VERSION 0.0.1 LANGUAGES CXX)

add_library(serial_bridge STATIC)

file(GLOB S_FILES src/source/*.cpp src/source/*.c)
file(GLOB H_FILES src/*.hpp src/*.h)

set(S_MCP2210 MCP2210-Library/mcp2210.cpp MCP2210-Library/hid.c)
set(H_MCP2210 MCP2210-Library/mcp2210.h MCP2210-Library/hidapi.h)

target_sources(serial_bridge
        PRIVATE
        ${S_MCP2210}
        ${S_FILES}
        )
set_property(TARGET serial_bridge
        PROPERTY PUBLIC_HEADER
        ${H_MCP2210}
        ${H_FILES}
        )
target_include_directories(serial_bridge
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> 
        $<INSTALL_INTERFACE:include>)

target_link_libraries(serial_bridge hidapi-hidraw)

install(TARGETS serial_bridge
        EXPORT libserial_bridge
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)