cmake_minimum_required(VERSION 3.16)

project(vivy)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(vivy
    src/main.cpp
)

target_link_libraries(vivy
    SDL2::SDL2
    SDL2_image::SDL2_image
)
