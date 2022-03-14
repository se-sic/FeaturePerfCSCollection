#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

volatile long Counter;

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, "--iterations");
  if (NumIterations)
    std::cout << "Number of Iterations: " << NumIterations << "\n";

  long CountTo = fpcsc::getRequiredFeatureValue(argc, argv, "--count_to");
  if (CountTo)
    std::cout << "In each iteration, count to: " << CountTo << "\n";


  if (NumIterations)
    for (long i = 0; i < NumIterations; ++i)
    {
      if (CountTo)
        for (Counter = 0; Counter < CountTo; ++Counter)
          ;
    }

  return 0;
}
