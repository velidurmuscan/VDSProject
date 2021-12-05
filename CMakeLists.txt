cmake_minimum_required(VERSION 3.10)
project(VDSProject CXX C)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 ${LLVM_CXX_FLAGS} ")

include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/test/)
link_directories(${CMAKE_SOURCE_DIR}/src/test/)

add_subdirectory(src)
add_executable(VDSProject src/main.cpp)
target_link_libraries(VDSProject Manager)

enable_testing()

set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} src/test/main_test.cpp)
target_link_libraries(${TEST_NAME} gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})