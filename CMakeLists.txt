cmake_minimum_required(VERSION 2.8.4)
project(Multithreading)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES_ELEVATOR Elevator.cpp )
add_executable(Elevator ${SOURCE_FILES_ELEVATOR})

set(SOURCE_FILES_StringParsing StringParsing.cpp StringParsing.h)
add_executable(StringParsing ${SOURCE_FILES_StringParsing})

set(SOURCE_FILES_Seq  Odd_Even_Threads.cpp)
add_executable(PrintSeq ${SOURCE_FILES_Seq})
