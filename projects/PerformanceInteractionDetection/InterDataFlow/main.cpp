#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Feature interaction case study (Data Flow):
/// Feature F1 interacts with performance-relevant code via data flow, i.e.,
/// data flows from code from F1 to performance-relevant code.

bool __attribute__((feature_variable("F1"))) F1;


int hotFunction(int t) {
  fp_util::sleep_for_millisecs(100 + t);
  return 0;
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");

  int t = 10;

  if (F1) {
    t *= 2;
  }

  hotFunction(t);

  return 0;
}
