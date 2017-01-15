cmake_minimum_required(VERSION 3.6)
project(AphroCite)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES AphroCite.h AphroCiteTest.c)
add_executable(AphroCite ${SOURCE_FILES})