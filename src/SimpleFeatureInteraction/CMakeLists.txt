add_test_binary("SimpleFeatureInteraction")

add_executable(SimpleFeatureInteraction SFImain.cpp)

set_target_properties(
  SimpleFeatureInteraction PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)
