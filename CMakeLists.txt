cmake_minimum_required(VERSION 3.28)
project(Asteroid-Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include/)

add_executable(main 
        src/main.cpp
        src/Entity.cpp
        src/Spaceship.cpp
        src/Asteroid.cpp
        src/Bullet.cpp
        src/Game.cpp
        src/Menu.cpp
        src/Settings.cpp
        src/MenuBase.cpp
        src/WindowManager.cpp
        src/ResourceManager.cpp
        src/GameObjectManager.cpp
        src/TextManager.cpp
)

target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_23)