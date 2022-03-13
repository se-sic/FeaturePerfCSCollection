#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

volatile long Counter;

int main(int argc, char *argv[]) {

  // Feature NumIteration
  long NumIterations = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--iterations"));
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  // Feature CountTo
  long CountTo = fpcsc::getRequiredFeatureValue(argc, argv, std::string("--count_to"));
  std::cout << "Count to " << CountTo << " in every iteration.\n";

  for (int i = 0; i < NumIterations; ++i) {
    if (CountTo) {
      for (Counter = 0; Counter < CountTo; ++Counter);
    }
  }

  return 0;
}
