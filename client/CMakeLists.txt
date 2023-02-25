cmake_minimum_required(VERSION 3.17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)

option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

configure_file(include/config.hpp config.hpp)

if (NOT USE_INSTALL_RESOURCE_PATH)
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/content/")
else ()
    set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/content/")
endif ()


set(SOURCES
        src/main.cpp
        src/cell.cpp
        src/board.cpp
        src/window.cpp
        src/game.cpp
        )

add_executable(client ${SOURCES})

target_include_directories(client PRIVATE "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(client
        PROPERTIES
        INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
        )


target_link_libraries(client
        all_protos sfml-system sfml-window sfml-graphics sfml-audio sfml-network
        )

install(TARGETS client DESTINATION bin)

install(DIRECTORY content
        DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
        )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
