project(STATE4C)

cmake_minimum_required(VERSION 2.8)
enable_testing()

set(CMAKE_C_FLAGS   "-Wall -Wextra -Werror")

include_directories(
    ${STATE4C_SOURCE_DIR}
)

add_library(state4c
    state4c.h
    state4c_go.c
    state4c_initialise.c
    state4c_setTransition.c
)

add_subdirectory(examples)
