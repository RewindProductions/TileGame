cmake_minimum_required(VERSION 2.6)

project(TileGame)

add_executable(TileGame
    quickcg.cpp
    main.cpp
)

find_package(SDL REQUIRED)
target_link_libraries(TileGame SDL)
