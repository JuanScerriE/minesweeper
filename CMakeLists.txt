cmake_minimum_required(VERSION 3.14)

project(
  minesweeper
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
