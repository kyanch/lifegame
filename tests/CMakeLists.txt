cmake_minimum_required(VERSION 3.14)

# New Policy for CMAKE 3.27+
cmake_policy(SET CMP0135 NEW)

# Uncomment twolines below, if you need Proxy.
# set(ENV{http_proxy} "http://127.0.0.1:7890")
# set(ENV{https_proxy} "http://127.0.0.1:7890")

# GoogleTest requires at least C++14
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB GL_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(lg_test ${GL_TEST_SOURCES})
target_link_libraries(lg_test GTest::gtest_main lifegame)

include(GoogleTest)
gtest_discover_tests(lg_test)