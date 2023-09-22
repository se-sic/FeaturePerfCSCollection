add_executable(Combined main.cpp)

target_compile_options(Combined PUBLIC -fno-exceptions)

set_target_properties(
  Combined PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
