add_executable(Runtime main.cpp)

target_compile_options(Runtime PUBLIC -fno-exceptions)

set_target_properties(
  Runtime PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
