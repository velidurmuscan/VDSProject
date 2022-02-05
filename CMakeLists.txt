cmake_minimum_required(VERSION 3.10)
project(VDSProject CXX C)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++14 ${LLVM_CXX_FLAGS} ")

include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/src/test/)
link_directories(${CMAKE_SOURCE_DIR}/src/test/)

#include_directories(${CMAKE_SOURCE_DIR}/src/reachability/)
#link_directories(${CMAKE_SOURCE_DIR}/src/reachability/)
################################
add_subdirectory(src/reachability/)
################################
include_directories(${CMAKE_SOURCE_DIR}/src/bench/)
link_directories(${CMAKE_SOURCE_DIR}/src/bench/)

include_directories(${CMAKE_SOURCE_DIR}/src/verify/)
link_directories(${CMAKE_SOURCE_DIR}/src/verify/)


add_subdirectory(src)
add_executable(VDSProject src/main.cpp)
target_link_libraries(VDSProject Manager)



#Boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
#Exe
add_subdirectory(src/bench)
add_executable(VDSProject_bench src/bench/main_bench.cpp)
target_link_libraries(VDSProject_bench Manager)
target_link_libraries(VDSProject_bench Benchmark)
target_link_libraries(VDSProject_bench ${Boost_LIBRARIES})



add_subdirectory(src/verify)
add_executable(VDSProject_verify src/verify/main_verify.cpp)


#add_executable(VDSProject_reachability src/reachability/Reachability.cpp src/reachability/Reachability.h src/reachability/ReachabilityInterface.h)
#target_link_libraries(VDSProject_reachability Manager)


enable_testing()

set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} src/test/main_test.cpp)
target_link_libraries(${TEST_NAME} gtest_main)



include(GoogleTest)
gtest_discover_tests(${TEST_NAME})




