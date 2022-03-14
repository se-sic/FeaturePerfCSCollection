#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

volatile long Counter;

int main(int argc, char *argv[])
{
  long NumIterations = fpcsc::getFeatureValue(argc, argv, "--iterations");

  if (!NumIterations)
    std::__throw_runtime_error("Required feature missing.");

  for (Counter = 0; Counter < NumIterations; ++Counter)
    ;

  return 0;
}
