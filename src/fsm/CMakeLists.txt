project(libfsm VERSION 0.1 LANGUAGES CXX)

add_library(fsm INTERFACE)

target_include_directories(fsm INTERFACE
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(fsm INTERFACE
  cxx_auto_type
  cxx_generic_lambdas)

install(TARGETS fsm EXPORT FSMConfig
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT FSMConfig DESTINATION share/FSM/cmake)
export(TARGETS fsm FILE FSMConfig.cmake)

add_executable(testfsm
  test/testmain.cpp
  test/teststate.cpp
  test/testedge.cpp
  test/testfsm.cpp)
target_link_libraries(testfsm fsm)

add_test(testfsm testfsm)
