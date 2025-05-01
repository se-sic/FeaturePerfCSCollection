#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {
  bool __attribute__((feature_variable("Slow"))) Slow = false;
  bool __attribute__((feature_variable("PreAlloc"))) PreAlloc = false;
  bool __attribute__((feature_variable("Header"))) Header = false;
  bool __attribute__((feature_variable("Feature4"))) Feature4 = false;

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--slow"))) {
    Slow = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--prealloc"))) {
    PreAlloc = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--header"))) {
    Header = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--f4"))) {
    Feature4 = true;
  }

  // Multiple regions related to --slow that take different amounts of time.

  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(3);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (Header) {
    fp_util::sleep_for_secs(3);
  } else {
    fp_util::sleep_for_secs(1);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (PreAlloc) {
    fp_util::sleep_for_secs(6);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (Feature4) {
    fp_util::sleep_for_secs(3);
  }

  return 0;
}
