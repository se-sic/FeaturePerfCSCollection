#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <cstdio>

/// This synthetic case study for whole program analysis
///
/// The key idea is that configuration code is spread all over the code base,
/// an inter-procedural whole program analysis.

int main(int argc, char *argv[]) {

  uint64_t Result{};

  fp_util::sleep_for_secs(3);
  std::printf("Result: %lu\n", Result);
  return 0;
}
