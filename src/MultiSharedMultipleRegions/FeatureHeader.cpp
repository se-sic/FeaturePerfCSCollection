#include "FeatureHeader.h"

bool ExternFeature = false;

static bool __attribute__((feature_variable("Cpp"))) CppFeature = false;

void enableCppFeature() {
  CppFeature = true;
}

bool isCppFeatureEnabled() {
  return CppFeature;
}
