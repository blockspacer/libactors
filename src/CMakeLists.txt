set(SOURCES
    actor.cpp
)

add_library(actors STATIC ${SOURCES})

install(TARGETS actors ARCHIVE DESTINATION lib64)
