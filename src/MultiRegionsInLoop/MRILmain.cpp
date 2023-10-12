// #include "fp_util/feature_cmd.h"
// #include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("NumIterations"))) NumIterations;
long __attribute__((feature_variable("Foo"))) Foo = 100;
long __attribute__((feature_variable("Bar"))) Bar = 200;

bool parseParams(int argc, char *argv[]) {
  NumIterations = fp_util::getFeatureValue(argc, argv, "--iterations");

  if (!NumIterations) {
    std::cerr << "Required feature missing."
              << "\n";
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (!parseParams(argc, argv)) {
    return 1;
  }

  for (long i = 0; i < NumIterations; ++i) {
    if (i > Foo) {
      fp_util::sleep_for_secs(1);
    }

    if (i > Bar) {
      fp_util::sleep_for_secs(1);
    }
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
