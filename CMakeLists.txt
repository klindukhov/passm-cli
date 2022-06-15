cmake_minimum_required(VERSION 3.22)
project(passm_cli)

set(CMAKE_CXX_STANDARD 23)

add_executable(passm_cli src/main.cpp src/Password.cpp include/passm_cli/Password.h src/Encryption.cpp include/passm_cli/Encryption.h src/CLI.cpp include/passm_cli/CLI.h src/File.cpp include/passm_cli/File.h)
