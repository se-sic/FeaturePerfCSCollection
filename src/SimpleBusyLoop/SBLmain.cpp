#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("NumIterations"))) NumIterations;
long CountTo;

bool parseParams(int argc, char *argv[]) {
  NumIterations = fpcsc::getFeatureValue(argc, argv, "--iterations");
  CountTo = fpcsc::getFeatureValue(argc, argv, "--count_to");

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

  return 0;
}
