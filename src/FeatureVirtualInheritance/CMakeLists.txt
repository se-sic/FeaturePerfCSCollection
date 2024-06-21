add_test_binary("FeatureVirtualInheritance")

add_executable(FeatureVirtualInheritance FVImain.cpp
        ../../projects/RecursiveCalls/RC.cpp
)

set_target_properties(
  FeatureVirtualInheritance PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
