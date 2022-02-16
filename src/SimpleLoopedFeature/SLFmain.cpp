#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>
#include <cassert>

int main(int argc, char *argv[]) {

  long int NumIterations = 0;
  fpcsc::getFeatureValue(argc, argv, std::string("--iterations"), &NumIterations);
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  long SleepFor;
  fpcsc::getFeatureValue(argc, argv, std::string("--sleepns"), &SleepFor);
  std::cout << "Nanoseconds to sleep: " << SleepFor << "\n";

  for (int i = 0; i < NumIterations; ++i) {
    fpcsc::sleep_for_nsecs (SleepFor);
  }

  return 0;
}
