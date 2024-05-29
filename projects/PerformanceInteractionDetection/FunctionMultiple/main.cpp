#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// Multiple hot functions case study.
/// Regression triggers only if function1 and function2 are affected.

bool __attribute__((feature_variable("F1"))) F1;
bool __attribute__((feature_variable("F2"))) F2;
bool __attribute__((feature_variable("F3"))) F3;


bool function1(int s) {
  if (s > 10) {
    return true;
  }
  return false;
}

void function2(bool b, int t) {
  if (b) {
    fp_util::sleep_for_millisecs(t * 100);
  }
  fp_util::sleep_for_millisecs(1000);
}

void function3() {
  fp_util::sleep_for_millisecs(1000);
}

int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");
  F2 = fp_util::isFeatureEnabled(argc, argv, "--f2");
  F3 = fp_util::isFeatureEnabled(argc, argv, "--f3");

  int s = 10;
  int t = 10;
  bool b = false;

  if (F1) {
    b = function1(s);
  }

  if (F2) {
    function2(b, t);
  }

  if (F3) {
    function3();
  }

  return 0;
}
