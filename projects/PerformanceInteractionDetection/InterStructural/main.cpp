#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Feature interaction case study (Structural):
/// Feature F1 interacts structurally with performance-relevant code, i.e.,
/// code from F1 is part of a performance-relevant code region.

bool __attribute__((feature_variable("F1"))) F1;


int hotFunction(int t) {
  if (F1) {
    t *= 2;
  }

  fp_util::sleep_for_millisecs(100 + t);
  return 0;
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");

  int t = 10;

  hotFunction(t);

  return 0;
}
