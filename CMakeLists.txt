cmake_minimum_required(VERSION 3.5)
project(CellServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Test/TestUdp.cpp include/cJSON.c include/cJSON.h Test/cJsonTest.cpp Test/RedisTest.cpp)
add_executable(CellServer ${SOURCE_FILES} Test/TestUdp.cpp include/cJSON.c include/cJSON.h Test/cJsonTest.cpp Test/RedisTest.cpp)