#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// This synthetic case study has a large (unconstrained) configuration space
/// where only a small portion affects the final sleep.
///
/// --f1  : enable f1
/// --f2  : enable f2
/// --f3  : enable f3
/// --f4  : enable f4
/// --f5  : enable f5
/// --f6  : enable f6
/// --f7  : enable f7
/// --f8  : enable f8
/// --f9  : enable f9
/// --f10 : enable f10
///

int main(int argc, char *argv[]) {
  bool F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");
  bool F2 = fp_util::isFeatureEnabled(argc, argv, "--f2");
  bool F3 = fp_util::isFeatureEnabled(argc, argv, "--f3");
  bool F4 = fp_util::isFeatureEnabled(argc, argv, "--f4");
  bool F5 = fp_util::isFeatureEnabled(argc, argv, "--f5");
  bool F6 = fp_util::isFeatureEnabled(argc, argv, "--f6");
  bool F7 = fp_util::isFeatureEnabled(argc, argv, "--f7");
  bool F8 = fp_util::isFeatureEnabled(argc, argv, "--f8");
  bool F9 = fp_util::isFeatureEnabled(argc, argv, "--f9");
  bool F10 = fp_util::isFeatureEnabled(argc, argv, "--f10");

  int sleepTime = 1000;

  if (F1) {
    if (!F4 && F10) {
      sleepTime = 2000;
    }
    fp_util::sleep_for_millisecs(50);
  }

  if (F2) {
    fp_util::sleep_for_millisecs(30);
  }

  if (F3) {
    fp_util::sleep_for_millisecs(10);
  }

  if (F4) {
    fp_util::sleep_for_millisecs(60);
  }

  if (F5) {
    if (F7 && !F3) {
      sleepTime *= 3;
    }
    fp_util::sleep_for_millisecs(70);
  }

  if (F6) {
    fp_util::sleep_for_millisecs(80);
  }

  if (F7) {
    fp_util::sleep_for_millisecs(40);
  }

  if (F8) {
    fp_util::sleep_for_millisecs(100);
  }

  if (F9) {
    fp_util::sleep_for_millisecs(90);
  }

  if (F10) {
    fp_util::sleep_for_millisecs(20);
  }

  fp_util::sleep_for_millisecs(sleepTime);
  return 0;
}
