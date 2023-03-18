set(SOURCES
        src/server.cpp
        src/game_session.cpp
        src/main.cpp
        model/src/board.cpp
        model/src/cell.cpp
        model/src/coordinates.cpp
        model/src/game.cpp
        model/src/player.cpp
        model/src/unit.cpp
        model/src/bfs_state.cpp
        interactors/src/choose_interactor.cpp
        interactors/src/move_interactor.cpp
        )

add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=address)

add_executable(server ${SOURCES})

target_include_directories(server PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/model/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/interactors/include")

set_target_properties(server
        PROPERTIES
        INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
        )

target_link_libraries(server
        all_protos
        )

install(TARGETS server DESTINATION bin)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

