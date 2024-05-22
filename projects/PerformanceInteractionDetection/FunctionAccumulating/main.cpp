#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Accumulating hot functions case study.
/// Regression accumulates over functions 1-3.

bool __attribute__((feature_variable("F1"))) F1;
bool __attribute__((feature_variable("F2"))) F2;
bool __attribute__((feature_variable("F3"))) F3;


void function1(int r) {
  fp_util::sleep_for_millisecs(100 + r);
}

void function2(int s) {
  fp_util::sleep_for_millisecs(100 + s);
}

void function3(int t) {
  fp_util::sleep_for_millisecs(100 + t);
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");
  F2 = fp_util::isFeatureEnabled(argc, argv, "--f2");
  F3 = fp_util::isFeatureEnabled(argc, argv, "--f3");

  int r = 10;
  int s = 10;
  int t = 10;

  if (F1) {
    function1(r);
  }

  if (F2) {
    function2(s);
  }

  if (F3) {
    function3(t);
  }

  return 0;
}
