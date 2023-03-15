set(SOURCES
        src/server.cpp
        src/game_session.cpp
        src/main.cpp
        )

add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=address)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


add_executable(server ${SOURCES})

target_include_directories(server PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/model/include")

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
