set(SOURCES
    demo.cpp
)

add_executable(demo ${SOURCES})
target_link_libraries(demo actors)
