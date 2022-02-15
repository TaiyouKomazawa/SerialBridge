cmake_minimum_required(VERSION 3.5)
project(serial_bridge VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON) 

add_library(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}
    PUBLIC -Wall
)

target_link_libraries(${PROJECT_NAME} udev)

add_subdirectory(src)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/MCP2210-Library/hid.c
    ${CMAKE_CURRENT_SOURCE_DIR}/MCP2210-Library/mcp2210.cpp
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-export
    LIBRARY         DESTINATION lib
    INCLUDES        DESTINATION include
    PUBLIC_HEADER   DESTINATION lib/${PROJECT_NAME}
)
   
install(EXPORT ${PROJECT_NAME}-export 
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION share/cmake/${PROJECT_NAME}/
)
