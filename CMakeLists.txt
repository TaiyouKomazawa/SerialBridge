cmake_minimum_required(VERSION 2.8)
project(SerialBridge CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(MAKE_DIRECTORY ./bin)
set(LIBRARY_OUTPUT_PATH ./bin)

add_subdirectory(src)
add_subdirectory(src/source)

include_directories(./src)

file(GLOB CXX_FILES ./src/source/*.cpp)
file(GLOB C_FILES ./src/source/*.c)

add_library(serial_bridge OBJECT ${CXX_FILES} ${C_FILES})
add_library(serial_bridge_static STATIC $<TARGET_OBJECTS:serial_bridge>)
add_library(serial_bridge_shared SHARED $<TARGET_OBJECTS:serial_bridge>)
