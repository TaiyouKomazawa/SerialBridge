cmake_minimum_required(VERSION 3.00)
project(serial_bridge VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-O -std=c++11 -Wall")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB S_FILES src/source/*.cpp src/source/*.c)
set(S_MCP2210 MCP2210-Library/mcp2210.cpp MCP2210-Library/hid.c)

add_library(sb_obj OBJECT ${S_MCP2210} ${S_FILES})

add_library(serial_bridge SHARED $<TARGET_OBJECTS:sb_obj>)
