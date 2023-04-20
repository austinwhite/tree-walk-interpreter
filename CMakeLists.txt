cmake_minimum_required(VERSION 3.22.1)
project(cpplox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(
  ${PROJECT_NAME}
  include/token.hpp
  src/token.cpp
  include/scanner.hpp
  src/scanner.cpp
  include/lox.hpp
  src/lox.cpp
  src/cli.cpp)
