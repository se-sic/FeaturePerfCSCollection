#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("NumIterations"))) NumIterations;
long CountTo;

bool parseParams(int argc, char *argv[]) {
  NumIterations = fp_util::getFeatureValue(argc, argv, "--iterations");
  CountTo = fp_util::getFeatureValue(argc, argv, "--count_to");

  if (!NumIterations || !CountTo) {
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
    for (long Counter = 0; Counter < CountTo; ++Counter) {
      asm volatile("" : "+g"(i), "+g"(Counter) : :); // prevent optimization
    }
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
