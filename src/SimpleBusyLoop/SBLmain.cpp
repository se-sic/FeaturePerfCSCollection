#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

volatile long Counter;

int main(int argc, char *argv[])
{
  std::string FeatureName = "--iterations";
  long NumIterations = fpcsc::getFeatureValue(argc, argv, FeatureName);

  if (NumIterations == FEATURE_MISSING)
    std::__throw_runtime_error(("Required Feature '" + FeatureName + "' is missing.").c_str());

  std::cout << "Number of Iterations: " << NumIterations << "\n";

  FeatureName = "--count_to";
  long CountTo = fpcsc::getFeatureValue(argc, argv, FeatureName);

  if (CountTo == FEATURE_MISSING)
    std::__throw_runtime_error(("Required Feature '" + FeatureName + "' is missing.").c_str());

  std::cout << "In each iteration, count to: " << CountTo << "\n";


  int i = 0;
  while (i < NumIterations)
  {
    Counter = 0;
    while (Counter < CountTo) {
      ++Counter;
    }

    ++i;
  }

  return 0;
}
