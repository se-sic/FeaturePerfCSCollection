add_executable(InsideLoop main.cpp)

target_compile_options(InsideLoop PUBLIC -fno-exceptions)

set_target_properties(
  InsideLoop PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
