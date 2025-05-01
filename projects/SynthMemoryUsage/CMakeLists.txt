add_executable(MemoryUsage main.cpp)

target_compile_options(MemoryUsage PUBLIC -fno-exceptions)

set_target_properties(
        MemoryUsage PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
