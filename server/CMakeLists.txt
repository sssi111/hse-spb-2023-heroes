set(SOURCES
        src/server.cpp
        src/main.cpp
        )

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
