cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(SOURCES
        src/client.cpp
        src/main.cpp
        src/cell.cpp
        src/board.cpp
        src/window.cpp
        src/game.cpp
        src/unit.cpp
        src/game_menu_bar.cpp
        src/event_manager.cpp
        src/resource_manager.cpp
        src/menu_button.cpp
        src/button.cpp
        src/coordinates.cpp
        src/textbox.cpp
        src/menu.cpp
        src/caption.cpp
        src/popup_window.cpp
        src/spell.cpp
        )

add_executable(client ${SOURCES})


target_include_directories(client PRIVATE
        "${PROJECT_BINARY_DIR}"
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
