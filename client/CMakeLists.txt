find_package(Threads)

set(SOURCES
        src/main.cpp
        )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

add_executable(client ${SOURCES})
target_link_libraries(client
        all_protos sfml-system sfml-window sfml-graphics sfml-audio sfml-network
        )
