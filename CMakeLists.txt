cmake_minimum_required(VERSION 3.6)
project(AphroCite C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c89 -Wall -Werror")

set(SOURCE_FILES AphroCite.h AphroCiteTest.c)
add_executable(AphroCite ${SOURCE_FILES})