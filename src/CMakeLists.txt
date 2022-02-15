cmake_minimum_required(VERSION 3.5)

add_subdirectory(source)

target_include_directories(${PROJECT_NAME} PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)
