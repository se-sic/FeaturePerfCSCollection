#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Feature interaction case study (Implicit Flow):
/// Code from F1 influences program state such that it implicitly affects data
/// that flows to performance-relevant code.

bool __attribute__((feature_variable("F1"))) F1;


int hotFunction(int t) {
  fp_util::sleep_for_millisecs(5000 + t * 100);
  return 0;
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");

  int t = 10;
  bool flag = false;

  if (F1) {
    flag = true;
  }

  if (flag) {
    t *= 2;
  }

  hotFunction(t);

  return 0;
}
