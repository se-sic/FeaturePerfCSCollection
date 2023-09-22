add_executable(Template2 main.cpp)

target_compile_options(Template2 PUBLIC -fno-exceptions)

set_target_properties(
  Combined PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
