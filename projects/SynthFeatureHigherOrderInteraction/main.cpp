#include "fp_util/feature_cmd.h"
#define USE_BUSY_SLEEPING
#include "fp_util/sleep.h"

/// This synthetic case study targets higher-order feature interactions.
///
/// --f1  : enable f1
/// --f2  : enable f2
/// --f3  : enable f3
/// --f4  : enable f4
/// --f5  : enable f5
/// --f6  : enable f6
/// --f7  : enable f7
/// --f8  : enable f8
///
/// The key idea is that configuration code can be dependent on very many
/// features at the same time.
///

int main(int argc, char *argv[]) {

  bool __attribute__((feature_variable("feature_1"))) F1 =
      fp_util::isFeatureEnabled(argc, argv, "--f1");
  bool __attribute__((feature_variable("feature_2"))) F2 =
      fp_util::isFeatureEnabled(argc, argv, "--f2");
  bool __attribute__((feature_variable("feature_3"))) F3 =
      fp_util::isFeatureEnabled(argc, argv, "--f3");
  bool __attribute__((feature_variable("feature_4"))) F4 =
      fp_util::isFeatureEnabled(argc, argv, "--f4");
  bool __attribute__((feature_variable("feature_5"))) F5 =
      fp_util::isFeatureEnabled(argc, argv, "--f5");
  bool __attribute__((feature_variable("feature_6"))) F6 =
      fp_util::isFeatureEnabled(argc, argv, "--f6");
  bool __attribute__((feature_variable("feature_7"))) F7 =
      fp_util::isFeatureEnabled(argc, argv, "--f7");
  bool __attribute__((feature_variable("feature_8"))) F8 =
      fp_util::isFeatureEnabled(argc, argv, "--f8");

  if (F1 || F2 || F3 || F4 || F5 || F6 || F7 || F8) {
    fp_util::sleep_for_millisecs(200);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1 && F2 && F3 && F4 && F5 && F6 && F7 && F8) {
    fp_util::sleep_for_millisecs(300);
  }

  fp_util::sleep_for_millisecs(111);

  if (F1) {
    fp_util::sleep_for_millisecs(100);

    if (F2) {
      fp_util::sleep_for_millisecs(200);

      if (F3) {
        fp_util::sleep_for_millisecs(300);

        if (F4) {
          fp_util::sleep_for_millisecs(400);

          if (F5) {
            fp_util::sleep_for_millisecs(500);

            if (F6) {
              fp_util::sleep_for_millisecs(600);

              if (F7) {
                fp_util::sleep_for_millisecs(700);

                if (F8) {
                  fp_util::sleep_for_millisecs(800);
                }
              }
            }
          }
        }
      }
    }
  }

  fp_util::sleep_for_millisecs(111);

  return 0;
}
