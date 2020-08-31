project(AbiuNote)

cmake_minimum_required(VERSION 3.10.2)

file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(AbiuNote ${src})