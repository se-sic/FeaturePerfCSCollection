#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[]) {

  long NumIterations = fpcsc::getFeatureValue(argc, argv, std::string("--iterations"));
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  if (NumIterations == -1) {
    std::__throw_runtime_error("Feature NumIterations missing.");
  }

  long SleepFor = fpcsc::getFeatureValue(argc, argv, std::string("--sleepms"));
  std::cout << "Milliseconds to sleep: " << SleepFor << "\n";

  if (SleepFor == -1) {
    std::__throw_runtime_error("Feature SleepFor missing.");
  }

  for (int i = 0; i < NumIterations; ++i) {
    if (SleepFor > 0) {
      fpcsc::sleep_for_millisecs (SleepFor);
    }
  }

  return 0;
}
