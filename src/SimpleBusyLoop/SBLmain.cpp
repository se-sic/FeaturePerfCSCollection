#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

volatile long Counter;

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, "--iterations");
  long CountTo = fpcsc::getRequiredFeatureValue(argc, argv, "--count_to");

  if (NumIterations)
    for (long i = 0; i < NumIterations; ++i)
    {
      if (CountTo)
        for (Counter = 0; Counter < CountTo; ++Counter)
          ;
    }

  return 0;
}
