#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getFeatureValue(argc, argv, "--iterations");
  long SleepFor = fpcsc::getFeatureValue(argc, argv, "--sleepms");

  if (!NumIterations || !SleepFor)
    std::__throw_runtime_error("Required feature missing.");

  if (NumIterations)
    for (long i = 0; i < NumIterations; ++i)
    {
      if (SleepFor)
        fpcsc::sleep_for_millisecs(SleepFor);
    }

  return 0;
}
