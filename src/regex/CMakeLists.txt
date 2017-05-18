add_executable(regex
  src/main.cpp
  src/regex.cpp)

target_link_libraries(regex fsm)
