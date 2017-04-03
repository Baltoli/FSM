cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_COMPILER clang)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

add_executable(fsm
  main.cc
  state.cc
)

target_link_libraries(fsm c++)
