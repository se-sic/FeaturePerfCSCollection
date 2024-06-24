//
// Created by abeltluk on 6/24/24.
//
#include "functions.h"

int main(int argc, char **argv) {
  FeatureA = fp_util::isFeatureEnabled(argc, argv, "--fA");
  FeatureB = fp_util::isFeatureEnabled(argc, argv, "--fB");
  FeatureC = fp_util::isFeatureEnabled(argc, argv, "--fC");

  fp_util::busy_sleep_for_millisecs(100);

  processFeatures();
}
