add_executable(Template main.cpp)

target_compile_options(Template PUBLIC)

set_target_properties(
  Template PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
