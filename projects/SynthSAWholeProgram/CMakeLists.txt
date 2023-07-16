add_executable(WholeProgram main.cpp config.cpp compute.cpp service.cpp)

set_target_properties(
  WholeProgram PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
