cmake_minimum_required(VERSION 3.16)
project(vivy LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find PkgConfig package
find_package(PkgConfig REQUIRED)

# Locate SDL2 and SDL2_image via pkg-config
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)

# Collect source files from src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Define the executable target
add_executable(vivy ${SOURCES})

# Apply compiler warning flags
target_compile_options(vivy PRIVATE -Wall -Wextra)

# Link SDL2 and SDL2_image targets (automatically handles include dirs & flags)
target_link_libraries(vivy PRIVATE
    PkgConfig::SDL2
    PkgConfig::SDL2_IMAGE
)

# Standard GNU installation directories (defines CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_DATADIR, etc.)
include(GNUInstallDirs)

# Install executable target to bin/ (e.g., /usr/local/bin/vivy)
install(TARGETS vivy
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install vivy.desktop if present
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vivy.desktop")
    install(FILES vivy.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    )
endif()
