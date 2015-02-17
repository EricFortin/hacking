
set(HEADERS )
set(SOURCES client.cpp)

add_executable(client ${SOURCES} ${HEADERS})

add_dependencies(client Common)
target_link_libraries(client Common)
