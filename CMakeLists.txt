cmake_minimum_required(VERSION 3.8)
project(ProceduralForest C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_ttf_INCLUDE_DIR})

add_executable(ProceduralForest main.c SDL_handler.c SDL_handler.h ProceduralGenerator.c ProceduralGenerator.h)

target_link_libraries(ProceduralForest
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_ttf_LIBRARIES})