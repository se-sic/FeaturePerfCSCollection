#include "FeatureHeader.h"

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {
  bool __attribute__((feature_variable("Slow"))) Slow = false;

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--slow"))) {
    Slow = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--header"))) {
    HeaderFeature = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--extern"))) {
    enableExternFeature();
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--cpp"))) {
    enableCppFeature();
  }

  // Multiple regions related to --slow that take different amounts of time.

  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(3);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (HeaderFeature) {
    fp_util::sleep_for_secs(3);
  } else {
    fp_util::sleep_for_secs(1);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (ExternFeature) {
    fp_util::sleep_for_secs(6);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (isCppFeatureEnabled()) {
    fp_util::sleep_for_secs(3);
  }

  return 0;
}
