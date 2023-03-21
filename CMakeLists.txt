cmake_minimum_required(VERSION 3.22)
project(hse-spb-2023-heroes LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if (NOT USE_INSTALL_RESOURCE_PATH)
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/client/content/")
else ()
    set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/client/content/")
endif ()

#add_link_options(-fsanitize=address)
#add_compile_options(-O0 -fsanitize=address)

configure_file(client/include/config.hpp.in config.hpp)

add_subdirectory(proto)
add_subdirectory(client)
add_subdirectory(server)
