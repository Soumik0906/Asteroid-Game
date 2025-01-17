cmake_minimum_required(VERSION 3.30)
project(Asteroid-Game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ROOT_DIR "${CMAKE_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/include/)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

file(GLOB SOURCES "${ROOT_DIR}/src/*.cpp")

add_executable(Asteroid-Game ${SOURCES})

target_compile_definitions(Asteroid-Game PRIVATE ROOT_DIR="${ROOT_DIR}")
target_link_libraries(Asteroid-Game PRIVATE sfml-window sfml-graphics sfml-audio)