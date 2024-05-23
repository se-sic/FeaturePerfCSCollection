#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

/// High interaction degree case study:
/// Regression is triggered only if all 10 features are enabled.

bool __attribute__((feature_variable("F1"))) F1;
bool __attribute__((feature_variable("F2"))) F2;
bool __attribute__((feature_variable("F3"))) F3;
bool __attribute__((feature_variable("F4"))) F4;
bool __attribute__((feature_variable("F5"))) F5;
bool __attribute__((feature_variable("F6"))) F6;
bool __attribute__((feature_variable("F7"))) F7;
bool __attribute__((feature_variable("F8"))) F8;
bool __attribute__((feature_variable("F9"))) F9;
bool __attribute__((feature_variable("F10"))) F10;


int main(int argc, char *argv[]) {
  F1 = fp_util::isFeatureEnabled(argc, argv, "--f1");
  F2 = fp_util::isFeatureEnabled(argc, argv, "--f2");
  F3 = fp_util::isFeatureEnabled(argc, argv, "--f3");
  F4 = fp_util::isFeatureEnabled(argc, argv, "--f4");
  F5 = fp_util::isFeatureEnabled(argc, argv, "--f5");
  F6 = fp_util::isFeatureEnabled(argc, argv, "--f6");
  F7 = fp_util::isFeatureEnabled(argc, argv, "--f7");
  F8 = fp_util::isFeatureEnabled(argc, argv, "--f8");
  F9 = fp_util::isFeatureEnabled(argc, argv, "--f9");
  F10 = fp_util::isFeatureEnabled(argc, argv, "--f10");

  int t = 10;

  if (F1) {
    if (F2) {
      if (F3) {
        if (F4) {
          if (F5) {
            if (F6) {
              if (F7) {
                if (F8) {
                  if (F9) {
                    if (F10) {
                      t *= 2;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  fp_util::sleep_for_millisecs(100 + t);
  return 0;
}
