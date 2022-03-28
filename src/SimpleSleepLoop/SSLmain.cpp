#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {
  long NumIterations = fpcsc::getFeatureValue(argc, argv, "--iterations");
  long SleepFor = fpcsc::getFeatureValue(argc, argv, "--sleepms");

  if (!NumIterations || !SleepFor) {
    std::cerr << "Required feature missing.";
    return 1;
  }

  for (long i = 0; i < NumIterations; ++i) {
    fpcsc::sleep_for_millisecs(SleepFor);
  }

  return 0;
}
