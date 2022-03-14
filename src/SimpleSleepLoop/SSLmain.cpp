#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

int main(int argc, char *argv[])
{
  std::string FeatureName = "--iterations";
  long NumIterations = fpcsc::getFeatureValue(argc, argv, FeatureName);

  if (NumIterations == FEATURE_MISSING)
    std::__throw_runtime_error(("Required Feature '" + FeatureName + "' is missing.").c_str());
  
  std::cout << "Number of Iterations: " << NumIterations << "\n";


  FeatureName = "--sleepms";
  long SleepFor = fpcsc::getFeatureValue(argc, argv, FeatureName);

  if (SleepFor == FEATURE_MISSING)
    std::__throw_runtime_error(("Required Feature '" + FeatureName + "' is missing.").c_str());

  std::cout << "Milliseconds to sleep: " << SleepFor << "\n";


  long i = 0;
  while (i < NumIterations)
  {
    fpcsc::sleep_for_millisecs(SleepFor);
    ++i;
  }

  return 0;
}
