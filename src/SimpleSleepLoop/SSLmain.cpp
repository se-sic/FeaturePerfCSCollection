#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--iterations"));
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  long SleepFor = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--sleepms"));
  std::cout << "Milliseconds to sleep: " << SleepFor << "\n";

  long i = 0;
  while (i < NumIterations) {
    fpcsc::sleep_for_millisecs(SleepFor);
    ++i;
  }

  return 0;
}
