cmake_minimum_required(VERSION 3.5)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/cobs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CobsSerial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MCP2210Linux.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SerialBridge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SyncableSerial.cpp
)
