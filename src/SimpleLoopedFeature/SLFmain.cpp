#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[]) {

  ___REGION_START __RT_High "NumIterations"

  long int NumIterations = 0;
  fpcsc::getFeatureValue(argc, argv, std::string("--iterations"), &NumIterations);
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  ___REGION_END __RT_High "NumIterations"

  ___REGION_START __RT_High "SleepFor"

  long SleepFor;
  fpcsc::getFeatureValue(argc, argv, std::string("--sleepns"), &SleepFor);
  std::cout << "Nanoseconds to sleep: " << SleepFor << "\n";

  ___REGION_END __RT_High "SleepFor"

  ___REGION_START __RT_High "NumIterations"

  for (int i = 0; i < NumIterations; ++i) {
    ___REGION_START __RT_High "SleepFor"

    fpcsc::sleep_for_nsecs (SleepFor);

    ___REGION_END __RT_High "SleepFor"
  }

  ___REGION_END __RT_High "NumIterations"

  return 0;
}
