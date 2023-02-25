cmake_minimum_required(VERSION 3.17)

project(sfml-draft)

set(CMAKE_CXX_STANDARD 17)

option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if (NOT USE_INSTALL_RESOURCE_PATH)
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/content/")
else ()
    set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/content/")
endif ()

configure_file(include/config.hpp config.hpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(sfml-draft src/main.cpp
        src/board.cpp
        src/window.cpp
        src/game.cpp)

set(SOURCES
        src/main.cpp
        )

target_include_directories(sfml-draft PRIVATE "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(sfml-draft
        PROPERTIES
        INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
        )

target_link_libraries(sfml-draft sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

install(TARGETS sfml-draft DESTINATION bin)

install(DIRECTORY content
        DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
        )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


add_executable(client ${SOURCES})
target_link_libraries(client
        all_protos sfml-system sfml-window sfml-graphics sfml-audio sfml-network
        )
