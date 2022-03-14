#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, "--iterations");
  long SleepFor = fpcsc::getRequiredFeatureValue(argc, argv, "--sleepms");

  if (NumIterations)
    for (long i = 0; i < NumIterations; ++i)
    {
      if (SleepFor)
        fpcsc::sleep_for_millisecs(SleepFor);
    }

  return 0;
}
