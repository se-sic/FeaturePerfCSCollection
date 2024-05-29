#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Single hot function case study.
/// Regression triggers if function1 is affected.

bool __attribute__((feature_variable("F1"))) F1;
bool __attribute__((feature_variable("F2"))) F2;
bool __attribute__((feature_variable("F3"))) F3;


void function1(int t) {
  fp_util::sleep_for_millisecs(1000 + t * 100);
}

void function2() {
  fp_util::sleep_for_millisecs(1000);
}

void function3() {
  fp_util::sleep_for_millisecs(1000);
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");
  F2 = fp_util::isFeatureEnabled(argc, argv, "--f2");
  F3 = fp_util::isFeatureEnabled(argc, argv, "--f3");

  int t = 10;

  if (F1) {
    function1(t);
  }

  if (F2) {
    function2();
  }

  if (F3) {
    function3();
  }

  return 0;
}
