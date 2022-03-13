#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[])
{
  // feature 'NumIterations'
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--iterations"));
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  // feature 'SleepFor'
  long SleepFor = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--sleepms"));
  std::cout << "Milliseconds to sleep: " << SleepFor << "\n";

  for (int i = 0; i < NumIterations; ++i)
  {
    if (SleepFor > 0)
    {
      fpcsc::sleep_for_millisecs(SleepFor);
    }
  }

  return 0;
}
