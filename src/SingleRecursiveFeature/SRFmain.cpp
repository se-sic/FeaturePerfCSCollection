#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

#include <string>


int recursiveFunction(long Recurse) {
  if (Recurse > 0) {
    fpcsc::sleep_for_millisecs(100);
    return recursiveFunction(Recurse - 1) + 2;
  }

  return 0;
}

int main(int argc, char *argv[] ) {
  long NumRecursiveCalls = fpcsc::getFeatureValue(argc, argv, "--recurse");

  return recursiveFunction(NumRecursiveCalls);
}
