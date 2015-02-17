

set(HEADERS PerfCounter.h Stats.h)

set(SOURCES PerfCounter.cpp)

add_library(Common STATIC ${SOURCES} ${HEADERS})