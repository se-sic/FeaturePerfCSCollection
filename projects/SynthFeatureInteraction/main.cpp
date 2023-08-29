#include "fp_util/feature_cmd.h"
#define USE_BUSY_SLEEPING
#include "fp_util/sleep.h"

/// This synthetic case study targets feature interactions.
///
/// --f1  : enable f1
/// --f2  : enable f2
/// --f3  : enable f3
///
/// The key idea is that configuration code is often dependent on different
/// feature combinations.
///

int main(int argc, char *argv[]) {

  bool __attribute__((feature_variable("feature_1"))) F1 =
      fp_util::isFeatureEnabled(argc, argv, "--f1");
  bool __attribute__((feature_variable("feature_2"))) F2 =
      fp_util::isFeatureEnabled(argc, argv, "--f2");
  bool __attribute__((feature_variable("feature_3"))) F3 =
      fp_util::isFeatureEnabled(argc, argv, "--f3");

  if (F1) {
    fp_util::sleep_for_millisecs(200);
  }

  fp_util::sleep_for_millisecs(111);

  if (F2) {
    fp_util::sleep_for_millisecs(300);
  }

  fp_util::sleep_for_millisecs(111);

  if (F3) {
    fp_util::sleep_for_millisecs(400);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 && F2) {
    fp_util::sleep_for_millisecs(120);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 || F2) {
    fp_util::sleep_for_millisecs(210);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 && F2 || F3) {
    fp_util::sleep_for_millisecs(132);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 || F2 && F3) {
    fp_util::sleep_for_millisecs(213);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 && F2 && F3) {
    fp_util::sleep_for_millisecs(123);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 || F2 || F3) {
    fp_util::sleep_for_millisecs(321);
  }

  return 0;
}
