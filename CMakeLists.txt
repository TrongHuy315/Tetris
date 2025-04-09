cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    SRC/main.cpp
    SRC/Game.cpp
    SRC/TetrominoParent.cpp
)

add_executable(Tetris ${SOURCES})

target_include_directories(Tetris PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SRC)

target_link_libraries(Tetris sfml-graphics sfml-window sfml-system)
