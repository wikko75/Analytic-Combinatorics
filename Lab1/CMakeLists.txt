cmake_minimum_required(VERSION 3.16)
project(Lab1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

#-pedantic-errors
set(FLAGS -fdiagnostics-color=always -g -ggdb -O2 -DNDEBUG -Wall -Wextra -Wsign-conversion)

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
