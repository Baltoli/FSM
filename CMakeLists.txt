cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(FSM VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

configure_file(FSMConfigVersion.cmake.in FSMConfigVersion.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FSMConfigVersion.cmake
  DESTINATION share/FSM/cmake)

enable_testing()

add_subdirectory(src)
add_subdirectory(doc)
