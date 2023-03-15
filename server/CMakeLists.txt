set(SOURCES
        src/main.cpp
        model/src/board.cpp
        model/src/cell.cpp
        model/src/coordinates.cpp
        model/src/game.cpp
        model/src/player.cpp
        model/src/unit.cpp
        model/src/bfs_state.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(server ${SOURCES})
target_link_libraries(server
        all_protos
        )
target_include_directories(server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/model/include")