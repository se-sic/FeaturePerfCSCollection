add_test_binary("PerfDetectiveExample")

add_executable(
  PerfDetectiveExample

  PDEmain.cpp
)

set_target_properties(MultiSharedMultipleRegions PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
