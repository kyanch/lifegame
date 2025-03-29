
file(GLOB LG_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(lifegame STATIC ${LG_SOURCES})
message(STATUS ${LG_SOURCES})
target_include_directories(lifegame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})