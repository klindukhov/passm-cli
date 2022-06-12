cmake_minimum_required(VERSION 3.22)
project(passm_cli)

set(CMAKE_CXX_STANDARD 23)

add_executable(passm_cli main.cpp Password.cpp Password.h)
