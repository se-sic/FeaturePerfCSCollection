#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>

static void performAction(void *Pointer) {
  asm volatile("" : : "g"(Pointer) : "memory");
}

int main(int argc, char *argv[]) {

  long int NumIterations = 0;
  fpcsc::getFeatureValue(argc, argv, std::string("--iterations"), &NumIterations);
  std::cout << "Number of Iterations: " << NumIterations << "\n";

  long SleepFor;
  bool Sleep = fpcsc::getFeatureValue(argc, argv, std::string("--sleepns"), &SleepFor);
  std::cout << "Nanoseconds to sleep: " << SleepFor << "\n";

  int SomeValue = 0;
  long int ActualIterations = 0;
  for (; ActualIterations < NumIterations; ++ActualIterations) {
    performAction (&SomeValue);

    if (SomeValue != 0)
      break;

    if (Sleep) {
      fpcsc::sleep_for_nsecs (SleepFor);
    }
  }

  std::cout << "Actual number of iterations: " << ActualIterations << "\n";

  return 0;
}
